const crypto = require('crypto');
const file = require('tmp-promise').file;
const fs = require('fs');
const path = require('path');
const { ShaderCache, shaderc, loadShader, loadProgram } = require('../../lib/shader');

// Payload definitions for testing.
const fragmentPath = path.resolve(__dirname, '');
const vertexPath = path.resolve(__dirname, '');
const includes = [path.resolve(__dirname, '')];
const defines = ['TEST_DEFINITION'];

describe('shaderc', () => {
  const checkBuild = async (inputPath, type, hash, preprocess) => {
    const { fd, path, cleanup } = await file();
    try {
      await shaderc(inputPath, path, type, { includes, defines, preprocess });

      const stream = fs.createReadStream(null, {fd});
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
    await checkBuild(vertexPath, 'vertex', 'foobar', true);
  });

  it('can build a vertex shader', async () => {
    await checkBuild(vertexPath, 'vertex', 'foobar', false);
  });

  it('can preprocess a fragment shader', async () => {
    await checkBuild(fragmentPath, 'fragment', 'foobar', true);
  });

  it('can build a fragment shader', async () => {
    await checkBuild(fragmentPath, 'fragment', 'foobar', false);
  });

  it('rejects invalid type', async () => {
    const { path, cleanup } = await file();
    try {
      expect(async () => {
        await shaderc(vertexPath, path, 'banana', { includes, defines });
      }).toThrow();
    } finally {
      cleanup();
    }
  });

  it('rejects invalid build params', async () => {
    const { path, cleanup } = await file();
    try {
      expect(async () => {
        await shaderc(vertexPath, path, 'vertex', {
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
    const result = await loadShader(vertexPath);
    expect(result).toBeDefined();
  })

  it('can load a fragment shader', () => {
    const result = await loadShader(fragmentPath);
    expect(result).toBeDefined();
  })
})

describe('loadProgram', () => {
  it('can load a program', () => {
    const result = await loadProgram(vertexPath, fragmentPath);
    expect(result).toBeDefined();
  })
})

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
      const result = await cache.load(vertexPath, 'vertex');
      expect(result).toEqual('foobar');
    });

    it('can load a fragment shader', async () => {
      const result = await cache.load(fragmentPath, 'fragment');
      expect(result).toEqual('foobar');
    });
  });

  describe('#program', () => {
    it('can create a shader program', async () => {
      const result = await cache.program(vertexPath, fragmentPath);
      expect(result).toBeDefined();
    });
  });
});
