/**
 * Generates bindings from the bgfx C99 API.
 */
const fs = require('fs');
const path = require('path');
const { lua, lauxlib, lualib } = require('fengari');

// Create a new Lua state in which to evaluate the bindings.
const L = lauxlib.luaL_newstate();
lualib.luaL_openlibs(L);

// Helper to print an error message and exit on error.
const check = status => {
  if (status) {
    throw new Error(`Error [${status}]: ${lua.lua_tojsstring(L, -1)}`);
  }
};

// Launch the Lua generator script.
check(lauxlib.luaL_dofile(L, path.join(__dirname, 'generate.lua')));

// Write the resulting binding strings to the source directories.
const bindingsCpp = lua.lua_tojsstring(L, -3);
fs.writeFileSync(path.join(__dirname, '../src/bgfx.cpp'), bindingsCpp);

const bindingsHpp = lua.lua_tojsstring(L, -2);
fs.writeFileSync(path.join(__dirname, '../src/bgfx.hpp'), bindingsHpp);

const bindingsJs = lua.lua_tojsstring(L, -1);
fs.writeFileSync(path.join(__dirname, '../enum.js'), bindingsJs);
