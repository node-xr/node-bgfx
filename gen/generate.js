/**
 * Generates bindings from the bgfx C99 API.
 */
const path = require("path");
const { luaconf, lua, lauxlib, lualib } = require("fengari");

const L = lauxlib.luaL_newstate();
lualib.luaL_openlibs(L);

/** Print an error message and exit on error. */
const check = status => {
  if (status === 0) return;
  console.error(`Error [${status}]: ${lua.lua_tojsstring(L, -1)}`);
  process.exit(status);
};

check(
  lauxlib.luaL_dofile(L, path.join(__dirname, "../deps/bgfx/scripts/idl.lua"))
);

check(
  lauxlib.luaL_dofile(L, path.join(__dirname, "../deps/bgfx/scripts/bgfx.idl"))
);

check(lauxlib.luaL_loadfile(L, "./util.lua"));
check(lauxlib.luaL_loadfile(L, "./napi.lua"));
check(lauxlib.luaL_dofile(L, "./generate.lua"));

//const repl = require("repl");
//Object.assign(repl.start("> ").context, { L, lua, lauxlib, lualib, fengari });
