const bgfx = require('../index');
const sdl = require('sdl2');

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
      DEVICE_LOST: 4
    });
  });

  describe('functions', () => {
    const { SDL_INIT_VIDEO, SDL_Init, SDL_Quit } = sdl;
    const { SDL_WINDOW_SHOWN, SDL_CreateWindow, SDL_GetWindowWMInfo } = sdl;
    let window;
    let info;

    beforeAll(() => {
      SDL_Init(SDL_INIT_VIDEO);
      window = SDL_CreateWindow('Test', 0, 0, 640, 480, SDL_WINDOW_SHOWN);
      info = SDL_GetWindowWMInfo(window);
    });

    afterAll(() => {
      SDL_DestroyWindow(window);
      SDL_Quit();
    });

    it('#init', () => {
      const { bgfx_init_minimal } = bgfx;
      // TODO: get window properties directly.
      // TODO: define enums properly.
      bgfx_init_minimal(info.display, info.window, 640, 480, 0x00000080);
    });
  });

  // TODO: add unit tests per function.
});
