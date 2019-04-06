const bgfx = require('bindings')('bgfx');
const enums = require('./enums');

const ATTRIB_SIZE = {
  FLOAT: 4,
  HALF: NaN,
  INT_16: 2,
  UINT_10: NaN,
  UINT_8: 1,
};

const ATTRIB_TYPEDARRAY = {
  FLOAT: Float32Array,
  HALF: undefined,
  INT_16: Int16Array,
  UINT_10: undefined,
  UINT_8: Uint8Array,
};

const isNumeric = key => typeof key !== 'symbol' && !isNaN(key);

const normalizeSpec = spec => {
  for (const field of spec) {
    if (!(field.attr in enums.ATTRIB))
      throw new Error(`Unsupported attribute '${field.attr}'.`);
    if (!(field.type in enums.ATTRIB_TYPE))
      throw new Error(`Unsupported attribute type '${field.attr}'.`);
    if (field.normalized === undefined) field.normalized = true;
    if (field.asInt === undefined) field.asInt = false;
  }
  return spec;
};

class VertexArray {
  constructor(spec, length, data) {
    this._spec = normalizeSpec(spec);

    // Compute the specification of this array.
    const { attrs, stride } = this._spec.reduce(
      ({ attrs, stride: offset }, field) => {
        const { attr, type, count } = field;
        const byteLength = ATTRIB_SIZE[type] * count;

        attrs[attr] = {
          getTypedArray: index =>
            new ATTRIB_TYPEDARRAY[type](
              this.data,
              index * this._stride + offset,
              count,
            ),
          count,
          byteLength,
        };

        const stride = offset + byteLength;
        return { attrs, stride };
      },
      { attrs: Object.create(null), stride: 0 },
    );
    this._attrs = attrs;
    this._stride = stride;

    // Allocate memory if it is not already allocated.
    if (data && length) {
      this.length = length;
      this.data = data;
      if (data.byteLength !== stride * length) {
        throw new Error(
          `Memory size ${data.byteLength} does not match ${stride * length}.`,
        );
      }
    } else if (data) {
      this.length = data.byteLength / stride;
      this.data = data;
      if (Number.isInteger(length))
        throw new Error(
          `Memory size ${data.byteLength} is not a multiple of ${stride}.`,
        );
    } else if (length) {
      this.length = length;
      this.data = new ArrayBuffer(stride * length);
    } else {
      throw new Error('Either a length or data buffer must be provided.');
    }

    // Create a proxy to allow [] access to elements.
    return new Proxy(this, {
      getPrototypeOf: () => VertexArray.prototype,
      get: (target, prop) =>
        isNumeric(prop) ? target.get(prop) : target[prop],
      set: (target, prop, value) => {
        if (isNumeric(prop)) {
          target.set(prop, value);
        } else {
          target[prop] = value;
        }
        return true;
      },
    });
  }

  // Get a view of this indexed element of the array.
  get(index) {
    const handlers = {
      get: (target, prop) => {
        const desc = this._attrs[prop];

        if (desc) {
          const { count, getTypedArray } = desc;
          const arr = getTypedArray(index);
          return count > 1 ? arr : arr[0];
        } else {
          return target[prop];
        }
      },
      set: (target, prop, value) => {
        const desc = this._attrs[prop];

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
          target[prop] = value;
          return true;
        }
      },
      ownKeys: _target => {
        return Object.keys(this._attrs);
      },
      getOwnPropertyDescriptor: (target, prop) => {
        return prop in this._attrs
          ? {
              configurable: true,
              enumerable: true,
              value: handlers.get(target, prop),
              writable: true,
            }
          : undefined;
      },
    };

    return new Proxy(Object.create(null), handlers);
  }

  set(index, value) {
    if (value === undefined)
      throw new Error('Cannot set() to undefined value.');

    const current = this.get(index);
    for (const attr of Object.keys(current)) {
      const v = value[attr];
      if (!v) throw new Error(`set() value was missing '${attr}'.`);
      current[attr].set(v);
    }

    return true;
  }

  [Symbol.iterator] = () => {
    let index = 0;
    return {
      next: () => ({
        done: index >= this.length,
        value: this.get(index++),
      }),
    };
  };

  clone() {
    return new VertexArray(this._spec, this.length, this.data.slice(0));
  }
}

class VertexBuffer {
  constructor(decl, length, data, options) {
    this.decl = decl;
    this.length = length;
    this.handle = undefined;

    this.options = {
      isDynamic: (options && options.isDynamic) || false,
      flags: (options && options.flags) || bgfx.BUFFER_NONE,
      name: options && options.name,
    };

    // Cache the correct setters for this buffer type.
    this._set_vertex_buffer = this.options.isDynamic
      ? bgfx.set_dynamic_vertex_buffer
      : bgfx.set_vertex_buffer;

    this._create_vertex_buffer = this.options.isDynamic
      ? bgfx.create_dynamic_vertex_buffer_mem
      : bgfx.create_vertex_buffer;

    // Create the memory array.
    this.array = new VertexArray(this.decl._spec, length, data);
  }

  upload() {
    if (!this.handle) {
      // Create a new vertex buffer in BGFX.
      this.handle = this._create_vertex_buffer(
        this.array._mem,
        this.decl._bgfx_decl,
        this.flags,
      );

      // We can do a few extra steps after uploading a static buffer.
      if (!this.isDynamic) {
        // Set a buffer name if provided.
        if (this.name)
          bgfx.set_vertex_buffer_name(this.handle, this.name, this.name.length);

        // Remove local memory if the upload is complete.
        delete this.array;
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
      numVertices || 0xffffffff,
    );
  }

  clone() {
    const { decl, length, array, options } = this;
    return new VertexBuffer(decl, length, array.data.slice(0), options);
  }

  /**
   * Create a vertex declaration from the provided object and
   * load the contents of the object into a VertexBuffer.
   *
   * @param obj the object containing one array per key.
   * @param forceFloat if set true, always only use a float type.
   */
  static from(obj, options) {
    const spec = [];
    let length = undefined;

    // Check for valid attributes and consistent length.
    for (const [attr, arr] of Object.entries(obj)) {
      // Are all the attributes in the supported bgfx enumeration?
      if (!(attr in enums.ATTRIB))
        throw new Error(`'${attr}' is not a valid bgfx attribute name`);

      // Are all the attribute arrays the same length?
      if (!arr.length) throw new Error(`'${attr}' cannot have empty array.`);
      else if (!length) length = arr.length;
      else if (length != arr.length)
        throw new Error(
          `'${attr}' array was length ${arr.length}, expected ${length}.`,
        );

      // Estimate the type of this array.
      const count = Array.isArray(arr[0]) ? arr[0].length : 1;
      const type = 'FLOAT';

      // Add this entry to the declaration.
      spec.push({ attr, type, count });
    }

    // Create a vertex declaration for this type.
    const decl = new VertexDeclaration(spec);
    const buffer = decl.allocate(length, options);

    // Fill in the buffer with array data.
    for (const [attr, arr] of Object.entries(obj)) {
      for (let i = 0; i < buffer.length; ++i) {
        buffer.array.get(i)[attr].set(arr[i]);
      }
    }

    return buffer;
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
          enums.ATTRIB[field.attr],
          field.count,
          enums.ATTRIB_TYPE[field.type],
          field.normalized,
          field.asInt,
        );
      }
    }
    bgfx.vertex_decl_end(this._bgfx_decl);
  }

  allocate(length, options) {
    if (!length || length <= 0) throw new Error('Allocate needs length >= 0');
    return new VertexBuffer(this, length, undefined, options);
  }

  wrap(mem, options) {
    if (!mem) throw new Error('Wrap needs a valid ArrayBuffer');
    return new VertexBuffer(this, undefined, mem, options);
  }
}

module.exports = exports = {
  ATTRIB_SIZE,
  ATTRIB_TYPEDARRAY,
  VertexArray,
  VertexBuffer,
  VertexDeclaration,
};
