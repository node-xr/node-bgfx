const child_process = require('child_process');
const fs = require('fs');
const os = require('os');
const path = require('path');
const util = require('util');

const { checksumFile } = require('./utils');
const { file } = require('tmp-promise');
const bgfx = require('bindings')('bgfx');
const execFile = util.promisify(child_process.execFile);
const flatCache = require('flat-cache');
const readFile = util.promisify(fs.readFile);

/**
 * Path to BGFX native executables.
 */
const BGFX_BINPATH = path.resolve(__dirname, '../deps/bgfx/bin');

/**
 * Mapping of BGFX platform strings for the current platform.
 * This is used in command-line arguments to BGFX tools.
 */
const BGFX_PLATFORM_ARGS = {
  darwin: { x64: ['--platform', 'osx', '-p', 'metal'] },
  linux: { x64: ['--platform', 'linux'] },
  win32: { x64: ['--platform', 'windows'] },
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

const shaderc = async (input, output, type, options) => {
  // Construct settings from provided options and defaults.
  const includes = (options && options.includes) || [];
  const defines = (options && options.defines) || [];
  const preprocess = (options && options.preprocess) || false;

  // Determine the platform settings to find the correct binary.
  const platform = os.platform();
  const arch = os.arch();

  // Compile the list of formatted arguments.
  const args = ['-f', input, '-o', output, '--type', type];
  args.push(...BGFX_PLATFORM_ARGS[platform][arch]);
  for (const include of includes) {
    args.push('-i', include);
  }
  if (defines.length) args.push('--define', defines.join(';'));
  if (preprocess) args.push('--preprocess');

  // Execute the actual shaderc call.
  const shadercBin = SHADERC_BIN[platform][arch];
  // console.debug(`Compiling shader: ${shadercBin} ${args.join(' ')}`);
  const { stdout } = await execFile(shadercBin, args);
  if (stdout) console.warn(stdout);
};

/**
 * Asynchronously load a shader from the provided path.
 *
 * @param {str} path the path to the compiled shader.
 */
const loadShader = async path => {
  const array = await readFile(path);
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
  return bgfx.create_program(await vShader, await fShader, true);
};

class ShaderCache {
  /**
   * Create a shader cache using the specified name and directory.
   *
   * @param {string} name the name of the cachefile to use
   * @param {string} directory optional path in which the cachefile is stored
   * @param {object} options 'includes' or 'defines' that will be used
   */
  constructor(name, directory, options) {
    this.cache = flatCache.create(name || 'bgfx_shader', directory);
    this.defines = (options && options.defines) || [];
    this.includes = (options && options.includes) || [
      path.resolve(__dirname, '../deps/bgfx/shaders'),
    ];
    this._platform = BGFX_PLATFORM[os.platform()][os.arch()];
  }

  /**
   * Loads a shader source from file and compiles on the fly if needed.
   *
   * @param {str} path path to the shader source file
   * @param {str} type type of the shader: 'fragment' or 'vertex'
   */
  async load(path, type) {
    const { cache, defines, includes } = this;

    // Check the type input to quickly throw an error.
    if (type !== 'vertex' && type !== 'fragment')
      throw new Error(`Unsupported shader type '${type}'.`);

    // Preprocess the shader first to cheaply resolve dependencies.
    const { path: prePath, cleanup: preCleanup } = await file();
    try {
      await shaderc(path, prePath, type, {
        includes,
        defines,
        preprocess: true,
      });

      // Take the md5 hash of the result and check if it is in the cache.
      const md5 = await checksumFile(prePath);
      const key = `${md5}.${this._platform}`;

      // If this hash is in the cache already, return the contents of the cache.
      const result = cache.getKey(key);
      if (result) {
        const shader = Buffer.from(result, 'base64');
        await bgfx.create_shader(shader.buffer); // TODO: de-duplicate this loading.
      }

      // If the result is not yet computed, compute it now and store the result.
      const { path: postPath, cleanup: postCleanup } = await file();
      try {
        await shaderc(prePath, postPath, type);

        // Store the resulting shader in the cache.
        const shader = await readFile(postPath);
        cache.setKey(key, shader.toString('base64'));
        cache.save(true);

        // Return the contents of the cache.
        return bgfx.create_shader(shader.buffer); // TODO: de-duplicate this loading.
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
    const vShader = this.load(vPath, 'vertex');
    const fShader = this.load(fPath, 'fragment');
    return bgfx.create_program(await vShader, await fShader, true);
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
  loadProgram,
  loadShader,
  shaderc,
  ShaderCache,
};
