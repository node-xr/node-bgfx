const bgfx = require('bindings')('bgfx');
const enums = require('./enums');

const ATTRIB_SIZE = {
  [enums.ATTRIB_TYPE.UINT_8]: 1,
  [enums.ATTRIB_TYPE.INT_16]: 2,
  [enums.ATTRIB_TYPE.FLOAT]: 4
};

const ATTRIB_TYPEDARRAY = {
  [enums.ATTRIB_TYPE.UINT_8]: Uint8Array,
  [enums.ATTRIB_TYPE.INT_16]: Int16Array,
  [enums.ATTRIB_TYPE.FLOAT]: Float32Array
};

const isNumeric = key => typeof key !== 'symbol' && !isNaN(key);

const attrLookup = (table, key) =>
  typeof key === 'string' ? table[key.toUpperCase()] : key;

const normalizeSpec = spec => {
  for (const field of spec) {
    field.attr = attrLookup(enums.ATTRIB, field.attr);
    field.type = attrLookup(enums.ATTRIB_TYPE, field.type);
    if (field.normalized === undefined) field.normalized = true;
    if (field.asInt === undefined) field.asInt = false;
  }
  return spec;
};

class VertexArray {
  constructor(spec, size, mem) {
    this._spec = normalizeSpec(spec);

    // Compute the specification of this array.
    const { attrs, stride } = this._spec.reduce(
      ({ attrs, stride }, field) => {
        const { attr, type, count } = field;
        const offset = stride;
        const byteLength = ATTRIB_SIZE[type] * count;

        attrs[attr] = {
          getTypedArray: index =>
            new ATTRIB_TYPEDARRAY[type](this._mem, stride, count),
          offset,
          count,
          byteLength
        };
        stride += byteLength;
        return { attrs, stride };
      },
      { attrs: {}, stride: 0 }
    );
    this._attrs = attrs;
    this._stride = stride;

    // Compute data indexing properties of the object.
    this._elemLength = size;
    this._byteLength = stride * size;

    // Allocate memory if it is not already allocated.
    if (mem) {
      if (mem.byteLength !== this._byteLength)
        throw new Error(
          `Memory size: expected ${this._byteLength}, got ${mem.byteLength}.`
        );
      this._mem = mem;
    } else {
      this._mem = new ArrayBuffer(this._byteLength);
    }

    // Create a proxy to allow [] access to elements.
    return new Proxy(this, {
      getPrototypeOf: () => VertexArray.prototype,
      get: (target, prop) =>
        isNumeric(prop) ? target.get(prop) : target[prop],
      set: (target, prop, value) => {
        if (isNumeric(prop)) {
          const current = target.get(prop);
          for (const [name, value] of Object.entries(value)) {
            current[name] = value;
          }
        } else {
          target[prop] = value;
        }
        return true;
      }
    });
  }

  // Get a view of this indexed element of the array.
  get(index) {
    return new Proxy(this, {
      get: (target, prop) => {
        const attr = attrLookup(enums.ATTRIB, prop);
        const desc = target._attrs[attr];

        if (desc) {
          const { count, getTypedArray } = desc;
          const arr = getTypedArray(index);
          return count > 1 ? arr : arr[0];
        } else {
          return undefined;
        }
      },
      set: (target, prop, value) => {
        const attr = attrLookup(enums.ATTRIB, prop);
        const desc = target._attrs[attr];

        if (desc) {
          const { count, getTypedArray } = desc;
          const arr = getTypedArray(index);

          if (count >= 1) {
            arr.set(value);
          } else {
            arr[0] = value;
          }
          return true;
        } else {
          return false;
        }
      },
      ownKeys: target => {
        return Object.keys(target._attrs);
      }
    });
  }

  get length() {
    return this._elemLength;
  }

  [Symbol.iterator]() {
    let index = 0;
    return {
      next: () => ({
        done: index === this._elemLength,
        value: this[index++] // TODO: fix this
      })
    };
  }

  clone() {
    return new VertexArray(this._spec, this._elemLength, this._mem.slice(0));
  }
}

class VertexBuffer {
  constructor(decl, size, options, mem) {
    this._decl = decl;
    this.size = size;
    this.handle = undefined;

    this.isDynamic = (options && options.isDynamic) || false;
    this.flags = (options && options.flags) || bgfx.BUFFER_NONE;
    this.name = options && options.name;

    // Cache the correct setters for this buffer type.
    this._set_vertex_buffer = this.isDynamic
      ? bgfx.set_dynamic_vertex_buffer
      : bgfx.set_vertex_buffer;

    this._create_vertex_buffer = this.isDynamic
      ? bgfx.create_dynamic_vertex_buffer_mem
      : bgfx.create_vertex_buffer;

    // Create the memory array.
    this.array = new VertexArray(this._decl._spec, size, mem);
  }

  upload() {
    if (!this.handle) {
      // Create a new vertex buffer in BGFX.
      this.handle = this._create_vertex_buffer(
        this.array._mem,
        this._decl._bgfx_decl,
        this.flags
      );

      // We can do a few extra steps after uploading a static buffer.
      if (!this.isDynamic) {
        // Set a buffer name if provided.
        if (this.name)
          bgfx.set_vertex_buffer_name(this.handle, this.name, this.name.length);

        // Remove local memory if the upload is complete.
        this.array = undefined;
      }
    } else if (this.isDynamic) {
      // Update the dynamic buffer to the new values.
      bgfx.update_dynamic_vertex_buffer(this.handle, 0, this.array._mem);
    } else {
      // Throw an error if we can't update.
      throw new Error('Cannot re-upload a static vertex buffer.');
    }

    // Return the handle to the uploaded vertex buffer.
    return this.handle;
  }

  set(startVertex, numVertices) {
    if (!this.handle)
      throw new Error('Cannot set a vertex buffer before it is uploaded.');

    this._set_vertex_buffer(
      0,
      this.handle,
      startVertex || 0,
      numVertices || 0xffffffff
    );
  }

  clone() {
    return new VertexBuffer(
      this._decl,
      this.size,
      { isDynamic: this.isDynamic, flags: this.flags, name: this.name },
      this.array._mem.slice(0)
    );
  }
}

class VertexDeclaration {
  constructor(spec) {
    this._spec = normalizeSpec(spec);
    this._bgfx_decl = bgfx.alloc_vertex_decl();

    bgfx.vertex_decl_begin(this._bgfx_decl, bgfx.get_renderer_type());
    {
      for (const field of this._spec) {
        bgfx.vertex_decl_add(
          this._bgfx_decl,
          field.attr,
          field.count,
          field.type,
          field.normalized,
          field.asInt
        );
      }
    }
    bgfx.vertex_decl_end(this._bgfx_decl);
  }

  allocate(size, options) {
    if (!size || size <= 0) throw new Error('Allocate requires positive size');
    return new VertexBuffer(this, size, options);
  }

  wrap(size, mem, options) {
    if (!size || size <= 0) throw new Error('Wrap requires positive size');
    if (!mem) throw new Error('Wrap requires a valid ArrayBuffer');
    return new VertexBuffer(this, size, options, mem);
  }

  static fromData() {}
}

exports.VertexDeclaration = VertexDeclaration;
exports.VertexArray = VertexArray;
