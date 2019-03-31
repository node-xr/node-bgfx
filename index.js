const bgfx = require('bindings')('bgfx');
const constants = require('./constants');
const enums = require('./enums');

// Include generated constants into the main export.
Object.assign(bgfx, constants);
Object.assign(bgfx, enums);

module.exports = bgfx;
