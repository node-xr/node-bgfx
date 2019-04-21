const SDL = require('sdl2');
const bgfx = require('bindings')('bgfx');

/**
 * Create an SDL/BGFX window to use BGFX functionality.
 */
const setupBgfxWindow = () => {
  let wnd;
  let info;

  beforeAll(() => {
    SDL.Init(SDL.INIT_VIDEO);
    wnd = SDL.CreateWindow('Test', 0, 0, 640, 480, SDL.WINDOW_SHOWN);
    info = SDL.GetWindowWMInfo(wnd);
    bgfx.init_minimal(info.display || null, info.window, 640, 480, 0x00000080);
  });

  afterAll(() => {
    bgfx.shutdown();
    SDL.DestroyWindow(wnd);
    SDL.Quit();
  });
};

module.exports = exports = {
  setupBgfxWindow,
};
