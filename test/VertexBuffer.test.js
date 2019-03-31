const bgfx = require('../index');
const helpers = require('./vertex.helpers');
const { VertexDeclaration } = require('../vertex');

describe('VertexBuffer', () => {
  let decl;
  let mem;

  beforeAll(() => {
    decl = new VertexDeclaration(helpers.specEnum);
    mem = new ArrayBuffer(16 * 100);
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

  describe('#wrap', () => {
    it('works with static buffers', () => {
      const buffer = decl.wrap(100, mem);
      expect(buffer).toBeDefined();
    });

    it('works with dynamic buffers', () => {
      const buffer = decl.wrap(100, mem, { isDynamic: true });
      expect(buffer).toBeDefined();
    });

    it('works with named buffers', () => {
      const buffer = decl.wrap(100, mem, { name: 'foo' });
      expect(buffer).toBeDefined();
    });

    it('works with flagged buffers', () => {
      const buffer = decl.wrap(100, mem, {
        flags: bgfx.BUFFER_COMPUTE_WRITE
      });
      expect(buffer).toBeDefined();
    });

    it('rejects mismatched buffers', () => {
      expect(() => {
        decl.wrap(-100, memIncorrect);
      }).toThrow();
    });

    it('rejects invalid sizes', () => {
      expect(() => {
        decl.wrap(-100, mem);
      }).toThrow();
    });

    it('rejects missing buffers', () => {
      expect(() => {
        decl.wrap(100, null);
      }).toThrow();
    });
  });

  describe('#clone', () => {
    it('works with static buffers', () => {
      const buffer = decl.allocate(100, { name: 'foo' });
      const clone = buffer.clone();
      expect(clone).toMatchObject({
        isDynamic: false,
        name: 'foo',
        size: buffer.size
      });
    });

    it('works with dynamic buffers', () => {
      const buffer = decl.allocate(100, { isDynamic: true, name: 'foo' });
      const clone = buffer.clone();
      expect(clone).toMatchObject({
        isDynamic: true,
        name: 'foo',
        size: buffer.size
      });
    });

    it('makes a copy of the buffer', () => {
      const buffer = decl.allocate(100);
      const clone = buffer.clone();

      const bufferView1 = new Int32Array(buffer.mem);
      const bufferView2 = new Int32Array(buffer.mem);
      const cloneView = new Int32Array(clone.mem);

      bufferView1[0] = 0xff00;

      expect(bufferView2[0]).toEqual(0xff00);
      expect(cloneView[0]).toEqual(0);
    });
  });
});
