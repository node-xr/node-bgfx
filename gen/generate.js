/**
 * Generates bindings from the bgfx C99 API.
 */
const fengari = require("fengari");
const { luaconf, lua, lauxlib, lualib } = fengari;

const L = lauxlib.luaL_newstate();
lualib.luaL_openlibs(L);

status = lauxlib.luaL_dofile(L, "../deps/bgfx/scripts/idl.lua");
status = lauxlib.luaL_dofile(L, "../deps/bgfx/scripts/bgfx.idl");
console.log(status);

status = lauxlib.luaL_loadfile(L, "./util.lua");
console.log(status);

status = lauxlib.luaL_loadfile(L, "./napi.lua");
console.log(status);

status = lauxlib.luaL_dofile(L, "./generate.lua");
console.log(status);

const repl = require("repl");
Object.assign(repl.start("> ").context, { L, lua, lauxlib, lualib, fengari });
