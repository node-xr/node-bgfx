const bgfx = require('bindings')('bgfx');
const constants = require('./constants');
const enums = require('./enums');
const VertexDeclaration = require('./VertexDeclaration');

// Include generated constants into the main export.
Object.assign(bgfx, constants);
Object.assign(bgfx, enums);

// Add helper classes.
bgfx.VertexDeclaration = VertexDeclaration;

module.exports = bgfx;
