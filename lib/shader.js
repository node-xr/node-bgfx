const crypto = require('crypto');
const fs = require('fs');
const os = require('os');
const path = require('path');
const util = require('util');

const bgfx = require('bindings')('bgfx');
const execFile = util.promisify(require('child_process').execFile);
const file = require('tmp-promise').file;
const flatCache = require('flat-cache');

/**
 * Path to BGFX native executables.
 */
const BGFX_BINPATH = path.resolve(__dirname, '../deps/bgfx/bin');

/**
 * Mapping of BGFX platform strings for the current platform.
 * This is used in command-line arguments to BGFX tools.
 */
const BGFX_PLATFORM = {
  darwin: { x64: 'osx' },
  linux: { x64: 'linux' },
  win32: { x64: 'windows' },
};

/**
 * Return the NAPI platform string for the current platform.
 * This is used in this package to determine which binaries to call.
 */
const SHADERC_BIN = {
  darwin: { x64: path.resolve(BGFX_BINPATH, 'darwin/x64/shadercRelease') },
  linux: { x64: path.resolve(BGFX_BINPATH, 'linux/x64/shadercRelease') },
  win32: { x64: path.resolve(BGFX_BINPATH, 'win32/x64/shadercRelease.exe') },
};

const shaderc = async (
  input,
  output,
  type,
  { includes, defines, preprocess },
) => {
  // Determine the platform settings to find the correct binary.
  const platform = os.platform();
  const arch = os.arch();

  // Compile the list of formatted arguments.
  const args = ['-f', input, '-o', output, '--type', type];
  args.push('--platform', BGFX_PLATFORM[platform][arch]);
  if (includes) args.push(includes.reduce((arr, d) => arr.push('-i', d), []));
  if (defines) args.push('--define', defines.join(';'));
  if (preprocess) args.push('--preprocess');

  // TODO: Remove this debug print.
  console.log({ args });

  // Construct the shaderc call with arguments.
  const { stdout } = await execFile(SHADERC_BIN[platform][arch], args);
  if (stdout) console.log(stdout); // TODO: Change this to debug level.
};

/**
 * Asynchronously load a shader from the provided path.
 *
 * @param {str} path the path to the compiled shader.
 */
const loadShader = async path => {
  const contents = await fs.readFile(path);
  const array = new Uint8Array(contents);
  return bgfx.create_shader(array.buffer);
};

/**
 * Asynchronusly load a fragment and vertex shader to create a shader program.
 *
 * @param {str} vPath path to vertex shader
 * @param {str} fPath path to fragment shader
 */
const loadProgram = async (vPath, fPath) => {
  const vShader = loadShader(vPath);
  const fShader = loadShader(fPath);
  return bgfx.create_program(await vShader, await fShader);
};

class ShaderCache {
  /**
   * Create a shader cache using the specified name and directory.
   *
   * @param {string} name the name of the cachefile to use
   * @param {string} directory optional path in which the cachefile is stored
   */
  constructor(name, directory) {
    this.cache = flatCache.create(name || 'bgfx_shader', directory);
    this.defines = [];
    this.includes = [path.resolve(__dirname, '../deps/bgfx/shaders')];
    this._platform = BGFX_PLATFORM[os.platform()][os.arch()];
  }

  /**
   * Loads a shader source from file and compiles on the fly if needed.
   *
   * @param {str} path path to the shader source file
   * @param {str} type type of the shader: 'fragment' or 'vertex'
   */
  async load(path, type) {
    const { includes, defines } = this;

    // Check the type input to quickly throw an error.
    if (type !== 'vertex' && type !== 'fragment')
      throw new Error(`Unsupported shader type '${type}'.`);

    // Preprocess the shader first to cheaply resolve dependencies.
    const { fd: preFd, path: prePath, cleanup: preCleanup } = await file();
    try {
      await shaderc(path, prePath, type, {
        includes,
        defines,
        preprocess: true,
      });

      // Take the md5 hash of the result and check if it is in the cache.
      const stream = fs.createReadStream(null, { fd: preFd });
      const md5Sum = crypto.createHash('md5');
      stream.pipe(md5Sum);
      const md5 = await new Promise((resolve, reject) => {
        md5Sum.on('end', () => resolve(md5Sum.read()));
        stream.on('error', reject); // TODO: do I need to close the hash?
      });
      const key = `${md5}.${this._platform}`;

      // If this hash is in the cache already, return the contents of the cache.
      const result = cache.getKey(key);
      if (result) return result.buffer;

      // If the result is not yet computed, compute it now and store the result.
      const { fd: postFd, path: postPath, cleanup: postCleanup } = await file();
      try {
        await shaderc(prePath, postPath, type);

        // Store the resulting shader in the cache.
        const stream = fs.createReadStream(null, { fd: postFd });
        const shader = new Uint8Array(stream.read());
        cache.setKey(key, shader);
        cache.save(true);

        return shader.buffer;
      } finally {
        postCleanup();
      }
    } finally {
      preCleanup();
    }
  }

  /**
   * Create a shader program from two source shaders.
   *
   * @param {str} vPath path to the vertex shader source
   * @param {str} fPath path to the fragment shader source
   */
  async program(vPath, fPath) {
    const vShader = this.load(vPath);
    const fShader = this.load(fPath);
    return bgfx.create_program(await vShader, await fShader);
  }

  destroy() {
    this.cache.destroy();
  }

  reset() {
    this.destroy();
    this.cache = flatCache.create(name || 'bgfx', directory);
  }
}

module.exports = exports = {
  ShaderCache,
  shaderc,
  loadShader,
  loadProgram,
};
