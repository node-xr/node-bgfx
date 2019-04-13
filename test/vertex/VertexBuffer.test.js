const SDL = require('sdl2');
const bgfx = require('../lib/index');
const { VertexDeclaration, VertexBuffer } = require('../lib/vertex');
const helpers = require('./vertex.helpers');

describe('VertexBuffer', () => {
  let decl;

  beforeAll(() => {
    decl = new VertexDeclaration(helpers.spec);
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

  describe('#wrap', () => {
    it('loads data from an object', () => {
      const buffer = VertexBuffer.wrap(helpers.buffer);
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
      bgfx.init_minimal(info.display || null, info.window, 640, 480, 0x00000080);
    });

    afterAll(() => {
      bgfx.shutdown();
      SDL.DestroyWindow(window);
      SDL.Quit();
    });

    it('works with static buffers', () => {
      const buffer = VertexBuffer.wrap(helpers.buffer);
      const handle = buffer.upload();
      expect(handle).toBeDefined();
      expect(handle).not.toEqual(bgfx.INVALID_HANDLE);
    });

    it('works with dynamic buffers', () => {
      const buffer = VertexBuffer.wrap(helpers.buffer, { isDynamic: true });
      const handle = buffer.upload();
      expect(handle).toBeDefined();
      expect(handle).not.toEqual(bgfx.INVALID_HANDLE);
    });
  });
});
