const bgfx = require('../index.js');
const SDL = require('sdl2');

const main = async () => {
  SDL.Init(SDL.INIT_VIDEO);
  const window = SDL.CreateWindow(
    'Test',
    SDL.WINDOWPOS_CENTERED,
    SDL.WINDOWPOS_CENTERED,
    640,
    480,
    SDL.WINDOW_SHOWN
  );
  const info = SDL.GetWindowWMInfo(window);

  if (!bgfx.init_minimal(info.display, info.window, 640, 480, 0x00000080))
    throw new Error('Failed to initialize BGFX');

  for (let i = 0; i < 255; ++i) {
    const color = (i << 24) + ((255 - i) << 16) + (i << 8) + 0xff;

    bgfx.set_view_rect_ratio(0, 0, 0, bgfx.BACKBUFFER_RATIO.EQUAL);
    bgfx.set_view_clear(0x0, 0x0001 | 0x0002, color, 0.0, 0);
    bgfx.touch(0x0);
    bgfx.frame(false);
  }

  bgfx.shutdown();
  SDL.DestroyWindow(window);
  SDL.Quit();
};

main();
