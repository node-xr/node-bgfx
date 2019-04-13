const os = require('os');
const path = require('path');

exports.fragment = {
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

exports.vertex = {
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

exports.includes = [path.resolve(__dirname, '../../deps/bgfx/shaders')];
exports.defines = ['TEST_DEFINITION'];
