const bgfx = require('../../lib/index.js');
const SDL = require('sdl2');

const s_cubePosition = [
  [-1.0, 1.0, 1.0],
  [1.0, 1.0, 1.0],
  [-1.0, -1.0, 1.0],
  [1.0, -1.0, 1.0],
  [-1.0, 1.0, -1.0],
  [1.0, 1.0, -1.0],
  [-1.0, -1.0, -1.0],
  [1.0, -1.0, -1.0],
];

const s_cubeColors = [
  [0xff, 0x00, 0x00, 0x00],
  [0xff, 0x00, 0x00, 0xff],
  [0xff, 0x00, 0xff, 0x00],
  [0xff, 0x00, 0xff, 0xff],
  [0xff, 0xff, 0x00, 0x00],
  [0xff, 0xff, 0x00, 0xff],
  [0xff, 0xff, 0xff, 0x00],
  [0xff, 0xff, 0xff, 0xff],
];

// prettier-ignore
const s_cubeTriList = [
  0, 1, 2, // 0
  1, 3, 2,
  4, 6, 5, // 2
  5, 6, 7,
  0, 2, 4, // 4
  4, 2, 6,
  1, 5, 3, // 6
  5, 7, 3,
  0, 4, 1, // 8
  4, 5, 1,
  2, 3, 6, // 10
  6, 3, 7,
];

// prettier-ignore
const s_cubeTriStrip = [
  0, 1, 2,
  3,
  7,
  1,
  5,
  0,
  4,
  2,
  6,
  7,
  4,
  5
];

// prettier-ignore
const s_cubeLineList = [
  0, 1,
  0, 2,
  0, 4,
  1, 3,
  1, 5,
  2, 3,
  2, 6,
  3, 7,
  4, 5,
  4, 6,
  5, 7,
  6, 7,
];

// prettier-ignore
const s_cubeLineStrip = [
  0, 2, 3, 1, 5, 7, 6, 4,
  0, 2, 6, 4, 5, 7, 3, 1,
  0
];

const s_cubePoints = [0, 1, 2, 3, 4, 5, 6, 7];

/*
fs.readFile('./myDirectoryContainingBinFiles/selectedFile.bin', function(
  err,
  data,
) {
  if (err) throw err;
  terrainData = new Uint16Array(toArrayBuffer(data));
});
*/

const main = async () => {
  const { CLEAR_COLOR, CLEAR_DEPTH, BUFFER_NONE } = bgfx;

  SDL.Init(SDL.INIT_VIDEO);
  // prettier-ignore
  const window = SDL.CreateWindow(
    'Example Cubes',
    SDL.WINDOWPOS_CENTERED, SDL.WINDOWPOS_CENTERED,
    640, 480, SDL.WINDOW_SHOWN,
  );
  const info = SDL.GetWindowWMInfo(window);

  // Initialize BGFX w/debug text.
  if (!bgfx.init_minimal(info.display, info.window, 640, 480, bgfx.RESET_VSYNC))
    throw new Error('Failed to initialize BGFX');
  bgfx.set_debug(bgfx.DEBUG_TEXT);

  // Set view 0 clear state.
  bgfx.set_view_clear(0, CLEAR_COLOR | CLEAR_DEPTH, 0x303030ff, 1.0, 0);

  const PosColorVertex = new bgfx.VertexDeclaration([
    { attr: 'POSITION', count: 3, type: 'FLOAT' },
    { attr: 'COLOR_0', count: 4, type: 'UINT_8', normalize: true },
  ]);

  const m_vbh = PosColorVertex.load({
    POSITION: s_cubePosition,
    COLOR_0: s_cubeColors,
  });

  // prettier-ignore
  const m_ibh = [
    bgfx.create_index_buffer(new Uint16Array(s_cubeTriList).buffer, BUFFER_NONE),
    bgfx.create_index_buffer(new Uint16Array(s_cubeTriStrip).buffer, BUFFER_NONE),
    bgfx.create_index_buffer(new Uint16Array(s_cubeLineList).buffer, BUFFER_NONE),
    bgfx.create_index_buffer(new Uint16Array(s_cubeLineStrip).buffer, BUFFER_NONE),
    bgfx.create_index_buffer(new Uint16Array(s_cubePoints).buffer, BUFFER_NONE),
  ];

  let i = 0;
  let time_last = process.hrtime.bigint();
  while (!SDL.QuitRequested()) {
    let time_curr = process.hrtime.bigint();
    const period_ms = Number(time_curr - time_last) / 1e6;

    // prettier-ignore
    bgfx.dbg_text_print(1, 1, 0x8f,
      `API ${bgfx.API_VERSION} - frame ${period_ms}ms`);
    bgfx.set_view_rect_ratio(0, 0, 0, bgfx.BACKBUFFER_RATIO.EQUAL);
    bgfx.touch(0x0);
    bgfx.frame(false);

    time_last = time_curr;
  }

  bgfx.shutdown();
  SDL.DestroyWindow(window);
  SDL.Quit();
};

main();
