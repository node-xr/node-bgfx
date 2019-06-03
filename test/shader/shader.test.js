const { file } = require('tmp-promise');
const {
  ShaderCache,
  shaderc,
  loadShader,
  loadProgram,
} = require('../../lib/shader');
const { checksumFile } = require('../../lib/utils');
const { setupBgfxWindow } = require('../helpers');
const { vertex, fragment, includes, defines } = require('./shader.helpers');
const bgfx = require('bindings')('bgfx');
const constants = require('../../lib/constants');

setupBgfxWindow();

describe('shaderc', () => {
  const checkBuild = async (inputPath, type, expectedPath, preprocess) => {
    const { path, cleanup } = await file();
    try {
      await shaderc(inputPath, path, type, { includes, defines, preprocess });
      const result = await checksumFile(path);
      const expected = await checksumFile(expectedPath);
      expect(result).toEqual(expected);
    } finally {
      cleanup();
    }
  };

  it('can preprocess a vertex shader', async () => {
    await checkBuild(vertex.source, 'vertex', vertex.preprocessed, true);
  });

  it('can build a vertex shader', async () => {
    await checkBuild(vertex.source, 'vertex', vertex.binary, false);
  });

  it('can preprocess a fragment shader', async () => {
    await checkBuild(fragment.source, 'fragment', fragment.preprocessed, true);
  });

  it('can build a fragment shader', async () => {
    await checkBuild(fragment.source, 'fragment', fragment.binary, false);
  });

  it('rejects invalid type', async () => {
    const { path, cleanup } = await file();
    try {
      await expect(
        shaderc(vertex.source, path, 'banana', { includes, defines }),
      ).rejects.toThrow();
    } finally {
      cleanup();
    }
  });

  it('rejects invalid include params', async () => {
    const { path, cleanup } = await file();
    try {
      await expect(
        shaderc(vertex.source, path, 'vertex', {
          includes,
          defines: [],
        }),
      ).rejects.toThrow();
    } finally {
      cleanup();
    }
  });

  it('rejects invalid define params', async () => {
    const { path, cleanup } = await file();
    try {
      await expect(
        shaderc(vertex.source, path, 'vertex', {
          includes: [],
          defines,
        }),
      ).rejects.toThrow();
    } finally {
      cleanup();
    }
  });
});

describe('loadShader', () => {
  it('can load a vertex shader', async () => {
    const handle = await loadShader(vertex.binary);
    expect(handle).toBeDefined();
    expect(handle).not.toEqual(constants.INVALID_HANDLE);
    bgfx.destroy_shader(handle);
  });

  it('can load a fragment shader', async () => {
    const handle = await loadShader(fragment.binary);
    expect(handle).toBeDefined();
    expect(handle).not.toEqual(constants.INVALID_HANDLE);
    bgfx.destroy_shader(handle);
  });
});

describe('loadProgram', () => {
  it('can load a program', async () => {
    const handle = await loadProgram(vertex.binary, fragment.binary);
    expect(handle).toBeDefined();
    expect(handle).not.toEqual(constants.INVALID_HANDLE);
    bgfx.destroy_program(handle);
  });
});

describe('ShaderCache', () => {
  let cache;

  beforeEach(() => {
    cache = new ShaderCache('test_bgfx', null, { defines });
  });

  afterAll(() => {
    cache.destroy();
  });

  describe('#load', () => {
    it('can load a vertex shader', async () => {
      const handle = await cache.load(vertex.source, 'vertex');
      expect(handle).toBeDefined();
      expect(handle).not.toEqual(constants.INVALID_HANDLE);
      bgfx.destroy_shader(handle);
    });

    it('can load a fragment shader', async () => {
      const handle = await cache.load(fragment.source, 'fragment');
      expect(handle).toBeDefined();
      expect(handle).not.toEqual(constants.INVALID_HANDLE);
      bgfx.destroy_shader(handle);
    });
  });

  describe('#program', () => {
    it('can create a shader program', async () => {
      const handle = await cache.program(vertex.source, fragment.source);
      expect(handle).toBeDefined();
      expect(handle).not.toEqual(constants.INVALID_HANDLE);
      bgfx.destroy_program(handle);
    });
  });
});
