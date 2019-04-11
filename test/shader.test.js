const { ShaderCache, shaderc } = require('../lib/shader');
const path = require('path');
const file = require('tmp-promise').file;

const fragmentPath = path.resolve(__dirname, '');
const vertexPath = path.resolve(__dirname, '');
const includes = path.resolve(__dirname, '');
const defines = path.resolve(__dirname, '');

describe('shaderc', () => {
  const checkBuild = async (file, type, hash, preprocess) => {
    const { fd, path, cleanup } = await file();
    try {
      await shaderc(file, path, type, { includes, defines, preprocess });

      const md5Sum = crypto.createHash('md5');
      preprocFd.pipe(md5Sum);
      const md5 = await new Promise((resolve, reject) => {
        md5Sum.on('end', () => resolve(md5Sum.read()));
        fd.on('error', reject); // TODO: do I need to close the hash?
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
});
