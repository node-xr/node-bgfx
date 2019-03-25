/**
 * Generates bindings from the bgfx C99 API.
 */
const path = require("path");
const { luaconf, lua, lauxlib, lualib } = require("fengari");

const L = lauxlib.luaL_newstate();
lualib.luaL_openlibs(L);

// Print an error message and exit on error.
const check = status => {
  if (status === 0) return;
  console.error(`Error [${status}]: ${lua.lua_tojsstring(L, -1)}`);
  process.exit(status);
};

// Launch the Lua generator script.
check(lauxlib.luaL_dofile(L, path.join(__dirname, "generate.lua")));
