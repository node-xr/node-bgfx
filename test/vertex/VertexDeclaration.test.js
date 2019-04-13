const bgfx = require('bindings')('bgfx');
const { VertexDeclaration } = require('../../lib/vertex');
const helpers = require('./vertex.helpers');

describe('VertexDeclaration', () => {
  let decl;
  let mem;

  beforeAll(() => {
    decl = new VertexDeclaration(helpers.spec);
    mem = new ArrayBuffer(16 * 100);
  });

  describe('#constructor', () => {
    it('handles valid spec', () => {
      expect(decl).toBeDefined();
    });

    it('rejects invalid attribute', () => {
      expect(() => {
        new VertexDeclaration(helpers.specInvalidAttr);
      }).toThrow();
    });

    it('rejects invalid type', () => {
      expect(() => {
        new VertexDeclaration(helpers.specInvalidType);
      }).toThrow();
    });
  });

  describe('#allocate', () => {
    it('works with static buffers', () => {
      const buffer = decl.allocate(100);
      expect(buffer).toBeDefined();
    });

    it('works with dynamic buffers', () => {
      const buffer = decl.allocate(100, { isDynamic: true });
      expect(buffer).toBeDefined();
    });

    it('works with named buffers', () => {
      const buffer = decl.allocate(100, { name: 'foo' });
      expect(buffer).toBeDefined();
    });

    it('works with flagged buffers', () => {
      const buffer = decl.allocate(100, { flags: bgfx.BUFFER_COMPUTE_WRITE });
      expect(buffer).toBeDefined();
    });

    it('rejects invalid sizes', () => {
      expect(() => {
        decl.allocate(-100);
      }).toThrow();
    });
  });

  describe('#load', () => {
    it('works with static buffers', () => {
      const buffer = decl.load(mem);
      expect(buffer).toBeDefined();
    });

    it('works with dynamic buffers', () => {
      const buffer = decl.load(mem, { isDynamic: true });
      expect(buffer).toBeDefined();
    });

    it('works with named buffers', () => {
      const buffer = decl.load(mem, { name: 'foo' });
      expect(buffer).toBeDefined();
    });

    it('works with flagged buffers', () => {
      const buffer = decl.load(mem, {
        flags: bgfx.BUFFER_COMPUTE_WRITE,
      });
      expect(buffer).toBeDefined();
    });

    it('rejects missing buffers', () => {
      expect(() => {
        decl.load(null);
      }).toThrow();
    });
  });

  describe('#wrap', () => {
    it('loads data from an object', () => {
      const buffer = decl.wrap(helpers.buffer);
      expect(buffer).toBeDefined();
      expect(buffer.array[0]).toBeDefined();

      for (let i = 0; i < helpers.buffer.POSITION.length; ++i) {
        expect(buffer.array[i].POSITION).toEqual(
          new Float32Array(helpers.buffer.POSITION[i]),
        );
        expect(buffer.array[i].COLOR_0).toEqual(
          new Uint8Array(helpers.buffer.COLOR_0[i]),
        );
      }
    });
  });
});
