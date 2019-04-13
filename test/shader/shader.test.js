const { file } = require('tmp-promise');
const {
  ShaderCache,
  shaderc,
  loadShader,
  loadProgram,
} = require('../../lib/shader');
const { checksumFile } = require('../../lib/utils');
const { vertex, fragment, includes, defines } = require('./shader.helpers');

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

  it('rejects invalid type', async () => {
    const { path, cleanup } = await file();
    try {
      expect(async () => {
        await shaderc(vertex.source, path, 'banana', { includes, defines });
      }).toThrow();
    } finally {
      cleanup();
    }
  });

  it('rejects invalid include params', async () => {
    const { path, cleanup } = await file();
    try {
      expect(async () => {
        await shaderc(vertex.source, path, 'vertex', {
          includes,
          defines: [],
        });
      }).toThrow();
    } finally {
      cleanup();
    }
  });

  it('rejects invalid define params', async () => {
    const { path, cleanup } = await file();
    try {
      expect(async () => {
        await shaderc(vertex.source, path, 'vertex', {
          includes: [],
          defines,
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
