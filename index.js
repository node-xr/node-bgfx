const bgfx = require('bindings')('bgfx');
const constants = require('./bgfx');

// Include the generated constants into the main export.
Object.assign(bgfx, constants);

module.exports = bgfx;
