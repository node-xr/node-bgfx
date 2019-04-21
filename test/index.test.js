const SDL = require('sdl2');
const bgfx = require('../lib/index');

describe('bgfx', () => {
  it('imports successfully', () => {
    expect(bgfx).toBeDefined();
  });

  it('includes enums', () => {
    expect(bgfx.FATAL).toMatchObject({
      DEBUG_CHECK: 0,
      INVALID_SHADER: 1,
      UNABLE_TO_INITIALIZE: 2,
      UNABLE_TO_CREATE_TEXTURE: 3,
      DEVICE_LOST: 4,
    });
  });

  it('does not round 64-bit constants', () => {
    expect(bgfx.STATE_MSAA).toEqual(0x0100000000000000n);
    expect(`${bgfx.STATE_MSAA}`).toEqual('72057594037927936');
  });

  describe('functions', () => {
    let wnd;
    let info;

    beforeAll(() => {
      SDL.Init(SDL.INIT_VIDEO);
      wnd = SDL.CreateWindow('Test', 0, 0, 640, 480, SDL.WINDOW_SHOWN);
      info = SDL.GetWindowWMInfo(wnd);
    });

    afterAll(() => {
      SDL.DestroyWindow(wnd);
      SDL.Quit();
    });

    it('#init_minimal', () => {
      // TODO: get window properties directly.
      // TODO: define enums properly.
      expect(
        bgfx.init_minimal(
          info.display || null,
          info.window,
          640,
          480,
          0x00000080,
        ),
      ).toEqual(true);

      bgfx.shutdown();
    });

    it('#init_headless', () => {
      expect(bgfx.init_headless()).toEqual(true);
      bgfx.shutdown();
    });
  });

  // TODO: add unit tests per function.
});
