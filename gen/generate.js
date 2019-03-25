/**
 * Generates bindings from the bgfx C99 API.
 */
const fs = require("fs");
const path = require("path");
const { lua, lauxlib, lualib } = require("fengari");

// Create a new Lua state in which to evaluate the bindings.
const L = lauxlib.luaL_newstate();
lualib.luaL_openlibs(L);

// Helper to print an error message and exit on error.
const check = status => {
  if (status === 0) return;
  console.error(`Error [${status}]: ${lua.lua_tojsstring(L, -1)}`);
  process.exit(status);
};

// Launch the Lua generator script.
check(lauxlib.luaL_dofile(L, path.join(__dirname, "generate.lua")));

// Write the resulting binding strings to the source directories.
const bindings_cpp = lua.lua_tojsstring(L, -3);
fs.writeFile(path.join(__dirname, "../src/bindings.cpp"), bindings_cpp);

const bindings_hpp = lua.lua_tojsstring(L, -2);
fs.writeFile(path.join(__dirname, "../src/bindings.hpp"), bindings_hpp);

const bindings_js = lua.lua_tojsstring(L, -1);
fs.writeFile(path.join(__dirname, "../bindings.js"), bindings_js);
