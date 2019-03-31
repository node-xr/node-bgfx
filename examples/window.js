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

  await sleep(5000);

  bgfx.shutdown();
  SDL.DestroyWindow(window);
  SDL.Quit();
};

main();
