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

// Payload definitions for testing.
const fragment = {
  src: path.resolve(__dirname, 'src/fs_uniformless.sc'),
  bin: path.resolve(
    __dirname,
    'bin',
    os.platform(),
    os.arch(),
    'fs_uniformless.bin',
  ),
};
const vertex = {
  src: path.resolve(__dirname, 'src/vs_uniformless.sc'),
  bin: path.resolve(
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
    const { fd, path, cleanup } = await file();
    try {
      await shaderc(inputPath, path, type, { includes, defines, preprocess });

      const stream = fs.createReadStream(null, { fd });
      const md5Sum = crypto.createHash('md5');
      stream.pipe(md5Sum);
      const md5 = await new Promise((resolve, reject) => {
        md5Sum.on('end', () => resolve(md5Sum.read()));
        stream.on('error', reject); // TODO: do I need to close the hash?
      });

      expect(md5).toEqual(hash);
    } finally {
      cleanup();
    }
  };

  it('can preprocess a vertex shader', async () => {
    await checkBuild(vertex.src, 'vertex', 'foobar', true);
  });

  it('can build a vertex shader', async () => {
    await checkBuild(vertex.src, 'vertex', 'foobar', false);
  });

  it('can preprocess a fragment shader', async () => {
    await checkBuild(fragment.src, 'fragment', 'foobar', true);
  });

  it('can build a fragment shader', async () => {
    await checkBuild(fragment.src, 'fragment', 'foobar', false);
  });

  it('rejects invalid type', async () => {
    const { path, cleanup } = await file();
    try {
      expect(async () => {
        await shaderc(vertex.src, path, 'banana', { includes, defines });
      }).toThrow();
    } finally {
      cleanup();
    }
  });

  it('rejects invalid build params', async () => {
    const { path, cleanup } = await file();
    try {
      expect(async () => {
        await shaderc(vertex.src, path, 'vertex', {
          includes: '',
          defines: '',
        });
      }).toThrow();
    } finally {
      cleanup();
    }
  });
});

describe('loadShader', () => {
  it('can load a vertex shader', async () => {
    const result = await loadShader(vertex.bin);
    expect(result).toBeDefined();
  });

  it('can load a fragment shader', async () => {
    const result = await loadShader(fragment.bin);
    expect(result).toBeDefined();
  });
});

describe('loadProgram', () => {
  it('can load a program', async () => {
    const result = await loadProgram(vertex.bin, fragment.bin);
    expect(result).toBeDefined();
  });
});

describe('ShaderCache', () => {
  let cache;

  beforeAll(() => {
    cache = new ShaderCache('test_bgfx');
  });

  afterAll(() => {
    cache.destroy();
  });

  describe('#load', () => {
    it('can load a vertex shader', async () => {
      const result = await cache.load(vertex.src, 'vertex');
      expect(result).toEqual('foobar');
      // TODO: release this shader?
    });

    it('can load a fragment shader', async () => {
      const result = await cache.load(fragment.src, 'fragment');
      expect(result).toEqual('foobar');
      // TODO: release this shader?
    });
  });

  describe('#program', () => {
    it('can create a shader program', async () => {
      const result = await cache.program(vertex.src, fragment.src);
      expect(result).toBeDefined();
      // TODO: release this program and shaders?
    });
  });
});
