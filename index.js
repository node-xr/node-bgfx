const constants = require("./bgfx");
const bgfx = require("bindings")("bgfx");

// TODO: add some customization here.
Object.assign(bgfx, constants);

module.exports = bgfx;
