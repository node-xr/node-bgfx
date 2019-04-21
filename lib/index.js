const bgfx = require('bindings')('bgfx');
const constants = require('./constants');
const enums = require('./enums');
const vertex = require('./vertex');
const shader = require('./shader');

// Include helpers in the main export.
Object.assign(bgfx, constants);
Object.assign(bgfx, enums);
Object.assign(bgfx, vertex);
Object.assign(bgfx, shader);

module.exports = bgfx;
