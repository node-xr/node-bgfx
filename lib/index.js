const bgfx = require('bindings')('bgfx');
const constants = require('./constants');
const enums = require('./enums');
const vertex = require('./vertex');

// Include helpers in the main export.
Object.assign(bgfx, constants);
Object.assign(bgfx, enums);
Object.assign(bgfx, vertex);

module.exports = bgfx;
