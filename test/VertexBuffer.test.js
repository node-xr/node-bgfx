const SDL = require('sdl2');
const bgfx = require('../lib/index');
const { VertexDeclaration, VertexBuffer } = require('../lib/vertex');
const helpers = require('./vertex.helpers');

describe('VertexBuffer', () => {
  let decl;
  let mem;

  beforeAll(() => {
    decl = new VertexDeclaration(helpers.spec);
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
      const buffer = decl.wrap(mem);
      expect(buffer).toBeDefined();
    });

    it('works with dynamic buffers', () => {
      const buffer = decl.wrap(mem, { isDynamic: true });
      expect(buffer).toBeDefined();
    });

    it('works with named buffers', () => {
      const buffer = decl.wrap(mem, { name: 'foo' });
      expect(buffer).toBeDefined();
    });

    it('works with flagged buffers', () => {
      const buffer = decl.wrap(mem, {
        flags: bgfx.BUFFER_COMPUTE_WRITE,
      });
      expect(buffer).toBeDefined();
    });

    it('rejects missing buffers', () => {
      expect(() => {
        decl.wrap(null);
      }).toThrow();
    });
  });

  describe('#clone', () => {
    it('works with static buffers', () => {
      const buffer = decl.allocate(100, { name: 'foo' });
      const clone = buffer.clone();
      expect(clone).toMatchObject({
        length: buffer.length,
        options: {
          name: 'foo',
        },
      });
    });

    it('works with dynamic buffers', () => {
      const buffer = decl.allocate(100, { isDynamic: true, name: 'foo' });
      const clone = buffer.clone();
      expect(clone).toMatchObject({
        length: buffer.length,
        options: {
          isDynamic: true,
          name: 'foo',
        },
      });
    });

    it('makes a copy of the buffer', () => {
      const buffer = decl.allocate(100);
      const clone = buffer.clone();

      const { POSITION: pos1 } = buffer.array[0];
      const { POSITION: pos2 } = buffer.array[0];
      const { POSITION: clonePos } = clone.array[0];

      pos1.set([23, 24, 25]);

      expect(pos2).toEqual(new Float32Array([23, 24, 25]));
      expect(clonePos).toEqual(new Float32Array([0, 0, 0]));
    });
  });

  describe('#from', () => {
    it('loads data from an object', () => {
      const buffer = VertexBuffer.from(helpers.buffer);
      expect(buffer).toBeDefined();
      expect(buffer.array[0]).toBeDefined();

      for (let i = 0; i < helpers.buffer.POSITION.length; ++i) {
        expect(buffer.array[i].POSITION).toEqual(
          new Float32Array(helpers.buffer.POSITION[i]),
        );
        expect(buffer.array[i].COLOR_0).toEqual(
          new Float32Array(helpers.buffer.COLOR_0[i]),
        );
      }
    });
  });

  describe('#upload', () => {
    let window;
    let info;

    beforeAll(() => {
      SDL.Init(SDL.INIT_VIDEO);
      window = SDL.CreateWindow('Test', 0, 0, 640, 480, SDL.WINDOW_SHOWN);
      info = SDL.GetWindowWMInfo(window);
      bgfx.init_minimal(info.display, info.window, 640, 480, 0x00000080);
    });

    afterAll(() => {
      bgfx.shutdown();
      SDL.DestroyWindow(window);
      SDL.Quit();
    });

    it('works with static buffers', () => {
      const buffer = VertexBuffer.from(helpers.buffer);
      const handle = buffer.upload();
      expect(handle).toBeDefined();
      expect(handle).not.toEqual(bgfx.INVALID_HANDLE);
    });

    it('works with dynamic buffers', () => {
      const buffer = VertexBuffer.from(helpers.buffer, { isDynamic: true });
      const handle = buffer.upload();
      expect(handle).toBeDefined();
      expect(handle).not.toEqual(bgfx.INVALID_HANDLE);
    });
  });
});
