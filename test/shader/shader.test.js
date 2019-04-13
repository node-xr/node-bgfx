const crypto = require('crypto');
const fs = require('fs');
const os = require('os');
const path = require('path');

const file = require('tmp-promise').file;
const {
  ShaderCache,
  shaderc,
  loadShader,
  loadProgram,
} = require('../../lib/shader');
const { checksumFile } = require('../../lib/util');

// Payload definitions for testing.
const fragment = {
  source: path.resolve(__dirname, 'src/fs_uniformless.sc'),
  preprocessed: path.resolve(__dirname, 'src/fs_uniformless_pp.sc'),
  binary: path.resolve(
    __dirname,
    'bin',
    os.platform(),
    os.arch(),
    'fs_uniformless.bin',
  ),
};
const vertex = {
  source: path.resolve(__dirname, 'src/vs_uniformless.sc'),
  preprocessed: path.resolve(__dirname, 'src/vs_uniformless_pp.sc'),
  binary: path.resolve(
    __dirname,
    'bin',
    os.platform(),
    os.arch(),
    'vs_uniformless.bin',
  ),
};
const includes = [path.resolve(__dirname, '../../deps/bgfx/shaders')];
const defines = ['TEST_DEFINITION'];

describe('shaderc', () => {
  const checkBuild = async (inputPath, type, hash, preprocess) => {
    const { path, cleanup } = await file();
    try {
      await shaderc(inputPath, path, type, { includes, defines, preprocess });
      const result = await checksumFile(path);
      expect(result).toEqual(hash);
    } finally {
      cleanup();
    }
  };

  it('can preprocess a vertex shader', async () => {
    await checkBuild(
      vertex.source,
      'vertex',
      await checksumFile(vertex.preprocessed),
      true,
    );
  });

  it('can build a vertex shader', async () => {
    await checkBuild(
      vertex.source,
      'vertex',
      await checksumFile(vertex.binary),
      false,
    );
  });

  it('can preprocess a fragment shader', async () => {
    await checkBuild(
      fragment.source,
      'fragment',
      await checksumFile(fragment.preprocessed),
      true,
    );
  });

  it('can build a fragment shader', async () => {
    await checkBuild(
      fragment.source,
      'fragment',
      await checksumFile(fragment.binary),
      false,
    );
  });

  it.skip('rejects invalid type', async () => {
    const { path, cleanup } = await file();
    try {
      expect(async () => {
        await shaderc(vertex.source, path, 'banana', { includes, defines });
      }).toThrow();
    } finally {
      cleanup();
    }
  });

  it.skip('rejects invalid build params', async () => {
    const { path, cleanup } = await file();
    try {
      expect(async () => {
        await shaderc(vertex.source, path, 'vertex', {
          includes: '',
          defines: '',
        });
      }).toThrow();
    } finally {
      cleanup();
    }
  });
});

describe.skip('loadShader', () => {
  it('can load a vertex shader', async () => {
    const result = await loadShader(vertex.binary);
    expect(result).toBeDefined();
  });

  it('can load a fragment shader', async () => {
    const result = await loadShader(fragment.binary);
    expect(result).toBeDefined();
  });
});

describe.skip('loadProgram', () => {
  it('can load a program', async () => {
    const result = await loadProgram(vertex.binary, fragment.binary);
    expect(result).toBeDefined();
  });
});

describe.skip('ShaderCache', () => {
  let cache;

  beforeAll(() => {
    cache = new ShaderCache('test_bgfx');
  });

  afterAll(() => {
    cache.destroy();
  });

  describe('#load', () => {
    it('can load a vertex shader', async () => {
      const result = await cache.load(vertex.source, 'vertex');
      expect(result).toEqual('foobar');
      // TODO: release this shader?
    });

    it('can load a fragment shader', async () => {
      const result = await cache.load(fragment.source, 'fragment');
      expect(result).toEqual('foobar');
      // TODO: release this shader?
    });
  });

  describe('#program', () => {
    it('can create a shader program', async () => {
      const result = await cache.program(vertex.source, fragment.source);
      expect(result).toBeDefined();
      // TODO: release this program and shaders?
    });
  });
});
