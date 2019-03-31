const bgfx = require('bindings')('bgfx');
const enums = require('./enums');

const ATTRIB_TYPE_SIZE = {
  [enums.ATTRIB_TYPE.UINT_8]: 1,
  [enums.ATTRIB_TYPE.INT_16]: 2,
  [enums.ATTRIB_TYPE.HALF]: 2,
  [enums.ATTRIB_TYPE.FLOAT]: 4
};

const normalizeSpec = spec => {
  for (const field of spec) {
    if (typeof field.attr === 'string')
      field.attr = enums.ATTRIB[field.attr.toUpperCase()];

    if (typeof field.type === 'string')
      field.type = enums.ATTRIB_TYPE[field.type.toUpperCase()];

    if (field.normalized === undefined) field.normalized = true;

    if (field.asInt === undefined) field.asInt = false;
  }
  return spec;
};

class VertexBuffer {
  constructor(decl, size, options, mem) {
    this._decl = decl;
    this.size = size;
    this.mem = mem;
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

    // Construct a memory buffer if it doesn't already exist.
    const stride = this._decl._spec.reduce(
      (acc, field) => acc + ATTRIB_TYPE_SIZE[field.type] * field.count,
      0
    );
    const numBytes = this.size * stride;

    if (this.mem === undefined) {
      // Allocate memory buffer.
      this.mem = new ArrayBuffer(numBytes);
    } else {
      // Verify the size of the memory buffer.
      const memBytes = this.mem.byteLength;
      if (memBytes !== numBytes)
        throw new Error(
          `Memory size mismatch: expected ${numBytes}, got ${memBytes}.`
        );
    }
  }

  upload() {
    if (!this.handle) {
      // Create a new vertex buffer in BGFX.
      this.handle = this._create_vertex_buffer(
        this.mem,
        this._decl,
        this.flags
      );

      if (!this.isDynamic) {
        // Set a buffer name if provided.
        if (this.name)
          bgfx.set_vertex_buffer_name(this.handle, this.name, this.name.length);

        // Remove local memory if the upload is complete.
        this.mem = undefined;
      }
    } else if (this.isDynamic) {
      // Update the dynamic buffer to the new values.
      bgfx.update_dynamic_vertex_buffer(this.handle, 0, this.mem);
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
    const other = new VertexBuffer(this._decl, this.size, this.isDynamic);
    this.mem = this.mem; // TODO: this is not right.
    return other;
  }
}

class VertexDeclaration {
  constructor(spec) {
    this._spec = normalizeSpec(spec);
    this._decl = bgfx.alloc_vertex_decl();

    bgfx.vertex_decl_begin(this._decl, bgfx.get_renderer_type());
    {
      for (const field of this._spec) {
        bgfx.vertex_decl_add(
          this._decl,
          field.attr,
          field.count,
          field.type,
          field.normalized,
          field.asInt
        );
      }
    }
    bgfx.vertex_decl_end(this._decl);
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
