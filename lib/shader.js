const flatCache = require('flat-cache');
const file = require('tmp-promise').file;
const crypto = require('crypto');
const os = require('os');
const path = require('path');
const util = require('util');
const execFile = util.promisify(require('child_process').execFile);

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
  darwin: { x64: path.resolve(BGFX_BINPATH, 'osx64/shadercRelease') },
  linux: { x64: path.resolve(BGFX_BINPATH, 'linux64/shadercRelease') },
  win32: { x64: path.resolve(BGFX_BINPATH, 'win64/shadercRelease.exe') },
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
  args.push(includes.reduce((arr, d) => arr.push('-i', d), []));
  args.push('--define', defines.join(';'));
  if (preprocess) args.push('--preprocess');

  // Construct the shaderc call with arguments.
  const { stdout } = execFile(SHADERC_BIN[platform][arch], args);

  // Remove this debug print.
  console.log({ shaderc, args });
  console.log(stdout);
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
  }

  async load(path, type) {
    const { includes, defines } = this;
    const platform = BGFX_PLATFORM[platform][arch];

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
      const md5Sum = crypto.createHash('md5');
      preFd.pipe(md5Sum);
      const md5 = await new Promise((resolve, reject) => {
        md5Sum.on('end', () => resolve(md5Sum.read()));
        fd.on('error', reject); // TODO: do I need to close the hash?
      });
      const key = `${md5}.${platform}`;

      // If this hash is in the cache already, return the contents of the cache.
      const result = cache.getKey(key);
      if (result) return result.buffer;

      // If the result is not yet computed, compute it now and store the result.
      const { fd: postFd, path: postPath, cleanup: postCleanup } = await file();
      try {
        await shaderc(prePath, postPath, type);

        // Store the resulting shader in the cache.
        const shader = new Uint8Array(postFd.read());
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
};
