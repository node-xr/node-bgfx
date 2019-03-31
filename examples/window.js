const bgfx = require('../index.js');
const SDL = require('sdl2');

const sleep = ms => {
  return new Promise(resolve => setTimeout(resolve, ms));
};

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

  bgfx.set_view_rect_ratio(0, 0, 0, bgfx.BACKBUFFER_RATIO.EQUAL);
  bgfx.set_view_clear(0x0, 0x0001 | 0x0002, 0xff00ffff, 0.0, 0);
  bgfx.touch(0x0);
  bgfx.frame(false);

  await sleep(5000);

  bgfx.shutdown();
  SDL.DestroyWindow(window);
  SDL.Quit();
};

main();
