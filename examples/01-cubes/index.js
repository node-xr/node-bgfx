const bgfx = require('../../lib/index.js');
const SDL = require('sdl2');
const fs = require('fs');
const path = require('path');
const { mat4, vec3 } = require('gl-matrix');

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

const fshader = new Uint8Array(
  fs.readFileSync(path.resolve(__dirname, 'shaders/glsl/fs_uniformless.bin')),
).buffer;

const vshader = new Uint8Array(
  fs.readFileSync(path.resolve(__dirname, 'shaders/glsl/vs_uniformless.bin')),
).buffer;

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

  // Create shaders.
  const m_program = bgfx.create_program(
    bgfx.create_shader(vshader),
    bgfx.create_shader(fshader),
    true,
  );

  const PosColorVertex = new bgfx.VertexDeclaration([
    { attr: 'POSITION', count: 3, type: 'FLOAT' },
    { attr: 'COLOR_0', count: 4, type: 'UINT_8', normalize: true },
  ]);

  const m_vbh = PosColorVertex.wrap({
    POSITION: s_cubePosition,
    COLOR_0: s_cubeColors,
  }).upload();

  // prettier-ignore
  const m_ibh = {
    triList: bgfx.create_index_buffer(new Uint16Array(s_cubeTriList).buffer, BUFFER_NONE),
    triStrip: bgfx.create_index_buffer(new Uint16Array(s_cubeTriStrip).buffer, BUFFER_NONE),
    lineList: bgfx.create_index_buffer(new Uint16Array(s_cubeLineList).buffer, BUFFER_NONE),
    lineStrip: bgfx.create_index_buffer(new Uint16Array(s_cubeLineStrip).buffer, BUFFER_NONE),
    cubePoint: bgfx.create_index_buffer(new Uint16Array(s_cubePoints).buffer, BUFFER_NONE),
  };

  let time_start = process.hrtime.bigint();
  let time_last = process.hrtime.bigint();
  while (!SDL.QuitRequested()) {
    let time_curr = process.hrtime.bigint();
    const period_ms = Number(time_curr - time_last) / 1e6;

    // prettier-ignore
    bgfx.dbg_text_print(1, 1, 0x8f,
      `API ${bgfx.API_VERSION} - frame ${period_ms}ms`);

    const at = vec3.fromValues(0.0, 0.0, 0.0);
    const eye = vec3.fromValues(0.0, 0.0, -35.0);
    const up = vec3.fromValues(0.0, 1.0, 0.0);

    const view = mat4.create();
    mat4.lookAt(view, eye, at, up);

    const proj = mat4.create();
    mat4.perspective(proj, 1.0, 640 / 480, 0.1, 100.0);

    bgfx.set_view_transform(0, view.buffer, proj.buffer);
    bgfx.set_view_rect_ratio(0, 0, 0, bgfx.BACKBUFFER_RATIO.EQUAL);

    bgfx.touch(0x0);

    // Submit 11x11 cubes.
    for (let yy = 0; yy < 11; ++yy) {
      for (let xx = 0; xx < 11; ++xx) {
        const mtx = mat4.create();
        mat4.translate(mtx, mtx, [(xx - 5) * 3.0, (yy - 5) * 3.0, 0]);
        mat4.rotateX(mtx, mtx, Number(time_curr - time_start) / 1e9);
        mat4.rotateY(mtx, mtx, Number(time_curr - time_start) / 1e9);

        // Set model matrix for rendering.
        bgfx.set_transform(mtx.buffer, 1);

        // Set vertex and index buffer.
        bgfx.set_vertex_buffer(0, m_vbh, 0, 0xffffffff);
        bgfx.set_index_buffer(m_ibh.triList, 0, 0xffffffff);

        // Set render states.
        bgfx.set_state(bgfx.STATE_DEFAULT, 0);

        // Submit primitive for rendering to view 0.
        bgfx.submit(0, m_program, 0, false);
      }
    }

    bgfx.frame(false);

    time_last = time_curr;
  }

  bgfx.shutdown();
  SDL.DestroyWindow(window);
  SDL.Quit();
};

main();
