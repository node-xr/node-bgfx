const bgfx = require('../../lib/index.js');
const SDL = require('sdl2');
const path = require('path');
const fs = require('fs');
const { mat4, vec3 } = require('gl-matrix');
const sharp = require('sharp');

// prettier-ignore
const s_cubePosition = [
  [-1.0,  1.0,  1.0],
  [ 1.0,  1.0,  1.0],
  [-1.0, -1.0,  1.0],
  [ 1.0, -1.0,  1.0],
  [-1.0,  1.0, -1.0],
  [ 1.0,  1.0, -1.0],
  [-1.0, -1.0, -1.0],
  [ 1.0, -1.0, -1.0],
  [-1.0,  1.0,  1.0],
  [ 1.0,  1.0,  1.0],
  [-1.0,  1.0, -1.0],
  [ 1.0,  1.0, -1.0],
  [-1.0, -1.0,  1.0],
  [ 1.0, -1.0,  1.0],
  [-1.0, -1.0, -1.0],
  [ 1.0, -1.0, -1.0],
  [ 1.0, -1.0,  1.0],
  [ 1.0,  1.0,  1.0],
  [ 1.0, -1.0, -1.0],
  [ 1.0,  1.0, -1.0],
  [-1.0, -1.0,  1.0],
  [-1.0,  1.0,  1.0],
  [-1.0, -1.0, -1.0],
  [-1.0,  1.0, -1.0],
];

// prettier-ignore
const s_cubeColors = [
  [0xff, 0x00, 0x00, 0x00],
  [0xff, 0x00, 0x00, 0xff],
  [0xff, 0x00, 0xff, 0x00],
  [0xff, 0x00, 0xff, 0xff],
  [0xff, 0xff, 0x00, 0x00],
  [0xff, 0xff, 0x00, 0xff],
  [0xff, 0xff, 0xff, 0x00],
  [0xff, 0xff, 0xff, 0xff],
  [0xff, 0x00, 0x00, 0x00],
  [0xff, 0x00, 0x00, 0xff],
  [0xff, 0x00, 0xff, 0x00],
  [0xff, 0x00, 0xff, 0xff],
  [0xff, 0xff, 0x00, 0x00],
  [0xff, 0xff, 0x00, 0xff],
  [0xff, 0xff, 0xff, 0x00],
  [0xff, 0xff, 0xff, 0xff],
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
   0,  2,  1,
   1,  2,  3,
   4,  5,  6,
   5,  7,  6,

   8,  9, 10,
   9, 11, 10,
  12, 14, 13,
  13, 14, 15,

  16, 18, 17,
  17, 18, 19,
  20, 21, 22,
  21, 23, 22,
];

// prettier-ignore
const s_cubeCoords = [
  [0.0, 0.0],
  [1.0, 0.0],
  [0.0, 1.0],
  [1.0, 1.0],
  [0.0, 0.0],
  [1.0, 0.0],
  [0.0, 1.0],
  [1.0, 1.0],
  [0.0, 0.0],
  [1.0, 0.0],
  [0.0, 1.0],
  [1.0, 1.0],
  [0.0, 0.0],
  [1.0, 0.0],
  [0.0, 1.0],
  [1.0, 1.0],
  [0.0, 0.0],
  [1.0, 0.0],
  [0.0, 1.0],
  [1.0, 1.0],
  [0.0, 0.0],
  [1.0, 0.0],
  [0.0, 1.0],
  [1.0, 1.0],
];

const width = 1280;
const height = 1024;

const main = async () => {
  const { CLEAR_COLOR, CLEAR_DEPTH, BUFFER_NONE } = bgfx;

  SDL.Init(SDL.INIT_VIDEO);
  // prettier-ignore
  const window = SDL.CreateWindow(
    'Example Cubes w/ Textures',
    SDL.WINDOWPOS_CENTERED, SDL.WINDOWPOS_CENTERED,
    width, height, SDL.WINDOW_SHOWN,
  );
  const info = SDL.GetWindowWMInfo(window);

  // Initialize BGFX w/debug text.
  // prettier-ignore
  if (
    !bgfx.init_minimal(
      info.display || null, info.window,
      width, height, bgfx.RESET_VSYNC,
    )
  )
    throw new Error('Failed to initialize BGFX');
  bgfx.set_debug(bgfx.DEBUG_TEXT);

  // Set view 0 clear state.
  bgfx.set_view_clear(0, CLEAR_COLOR | CLEAR_DEPTH, 0x303030ff, 1.0, 0);

  // Create shaders.
  const cache = new bgfx.ShaderCache();
  const m_program = await cache.program(
    path.resolve(__dirname, 'vs_flat.sc'),
    path.resolve(__dirname, 'fs_flattextured.sc'),
  );

  const PosColorVertex = new bgfx.VertexDeclaration([
    { attr: 'POSITION', count: 3, type: 'FLOAT' },
    { attr: 'COLOR_0', count: 4, type: 'UINT_8', normalize: true },
    { attr: 'TEX_COORD_0', count: 2, type: 'FLOAT' },
  ]);

  const u_baseColor = bgfx.create_uniform(
    'u_baseColor',
    bgfx.UNIFORM_TYPE.VEC_4,
    1,
  );

  const s_diffuse = bgfx.create_uniform(
    's_diffuse',
    bgfx.UNIFORM_TYPE.SAMPLER,
    1,
  );

  // Load a KTX texture from file.
  //
  // This format is natively supported by BGFX, so we can directly pass
  // it into the `create_texture()` method.
  const ktxFilename = path.join(__dirname, 'eagle2.ktx');
  const ktxMem = fs.readFileSync(ktxFilename);
  const { handle: ktxTexture, info: ktxInfo } = bgfx.create_texture(
    ktxMem.buffer,
    bgfx.TEXTURE_NONE,
    0,
  );
  console.log(`Loaded KTX texture: ${ktxFilename}`);
  console.log(ktxInfo);

  // Load a JPEG texture from file.
  //
  // This format is not natively supported, so we use the `sharp`
  // module to first load it into a buffer, then initialize that
  // buffer within BGFX.  Note that the `sharp` library is not a
  // runtime dependency for this library.
  const jpgFilename = path.join(__dirname, 'eagle_inverted.jpg');
  const jpgSharp = sharp(jpgFilename).raw();
  const jpgImage = await jpgSharp.toBuffer({ resolveWithObject: true });
  const jpgTexture = bgfx.create_texture_2d(
    jpgImage.info.width,
    jpgImage.info.height,
    false,
    1,
    bgfx.TEXTURE_FORMAT.RGB8,
    bgfx.TEXTURE_NONE,
    jpgImage.data.buffer,
  );
  console.log(`Loaded JPG texture: ${jpgFilename}`);
  console.log(jpgImage.info);

  const m_vbh = PosColorVertex.wrap({
    POSITION: s_cubePosition,
    COLOR_0: s_cubeColors,
    TEX_COORD_0: s_cubeCoords,
  }).upload();

  const m_ibh = bgfx.create_index_buffer(
    new Uint16Array(s_cubeTriList).buffer,
    BUFFER_NONE,
  );

  const at = vec3.fromValues(0.0, 0.0, 0.0);
  const eye = vec3.fromValues(0.0, 0.0, -35.0);
  const up = vec3.fromValues(0.0, 1.0, 0.0);

  const mtx = mat4.create();
  const view = mat4.create();
  const proj = mat4.create();

  const span = 11;
  const cubes = new Array(span).fill(0).map(() => new Array(span).fill(0));

  // Pre-construct the draw calls to modify and submit on the fly.
  for (let yy = 0; yy < span; ++yy) {
    for (let xx = 0; xx < span; ++xx) {
      const baseColor = Float32Array.from([xx / span, yy / span, 0.5, 1.0])
        .buffer;

      cubes[xx][yy] = {
        xform: mtx.buffer,
        vertex: m_vbh,
        index: m_ibh,
        uniforms: {
          [u_baseColor]: baseColor,
        },
        textures: {
          [s_diffuse]: {
            stage: 0,
            texture: xx % 2 ? ktxTexture : jpgTexture,
          },
        },
        program: m_program,
        view: 0,
      };
    }
  }

  let time_start = process.hrtime.bigint();
  let time_last = process.hrtime.bigint();

  while (!SDL.QuitRequested()) {
    let time_curr = process.hrtime.bigint();
    const dt = Number((time_curr - time_start) / 1000000n) / 1e3;
    const period_ms = Number(time_curr - time_last) / 1e6;

    // prettier-ignore
    bgfx.dbg_text_print(1, 1, 0x8f, `API ${bgfx.API_VERSION} - frame ${period_ms}ms`);

    mat4.lookAt(view, eye, at, up);
    mat4.perspective(proj, 1.0, width / height, 0.1, 300.0);

    bgfx.set_view_transform(0, view.buffer, proj.buffer);
    bgfx.set_view_rect_ratio(0, 0, 0, bgfx.BACKBUFFER_RATIO.EQUAL);

    bgfx.touch(0x0);

    // Submit cubes via draw() call.
    const draw_begin = process.hrtime.bigint();
    for (let yy = 0; yy < span; ++yy) {
      for (let xx = 0; xx < span; ++xx) {
        // The cubes share a transformation that updates between draw() calls.
        mat4.fromTranslation(mtx, [
          (xx - span / 2) * 3.0,
          (yy - span / 2) * 3.0,
          0,
        ]);
        mat4.rotateX(mtx, mtx, xx + dt);
        mat4.rotateY(mtx, mtx, yy + dt);

        // Use unified draw() call.
        bgfx.draw(cubes[xx][yy]);
      }
    }
    const draw_end = process.hrtime.bigint();

    const draw_time = Number(draw_end - draw_begin) / 1e6;
    console.log(`submit ${draw_time}ms`);

    bgfx.frame(false);
    time_last = time_curr;
  }

  bgfx.shutdown();
  SDL.DestroyWindow(window);
  SDL.Quit();
};

main();
