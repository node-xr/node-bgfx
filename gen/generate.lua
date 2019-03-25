local idl = require("./deps/bgfx/scripts/idl")
local util = require("./gen/util")
local napi = require("./gen/napi")
local to_snake_case = util.to_snake_case

-- Load the BGFX interface description file.
do
  local bgfx_idl, err = loadfile("./deps/bgfx/scripts/bgfx.idl", "t", idl)
  print(bgfx_idl, err)
  bgfx_idl()
end

local function format_enum_entry(key, value, needs_comma, comment, indent)
  indent = string.rep(" ", indent or 2)
  return indent .. string.format("%-20s: %2d%s", key, value, 
    ((needs_comma and ",") or " ") .. ((comment and " // "..comment) or ""))
end

local function gen_enum(e)
  local frags = {"bgfx." .. to_snake_case(e.name):upper() .. " = {"}
  for i, v in ipairs(e['enum']) do
    local keyname = to_snake_case(v.name):upper()
    local needs_comma = (i ~= #e['enum'])
    frags[#frags+1] = format_enum_entry(keyname, i-1, needs_comma, v.comment)
  end
  frags[#frags+1] = "}"
  return table.concat(frags, "\n")
end

local n_success, n_err  = 0, 0

local dest_cpp = ''
local dest_hpp = ''
local dest_js  = ''

-- lets just print out enums for testing
for k, v in pairs(idl.types) do
  if v['enum'] then 
    dest_js = dest_js .. gen_enum(v)
    dest_js = dest_js .. "\n\n"
    napi:add_enum_type(v.name .. "::Enum", v)
  elseif v.handle then
    napi:add_handle_type(v.name, v)
  end
end

for k, v in pairs(idl.funcs) do
  if (not v.class) and (not v.cpponly) then
    local signature, body, had_errors = napi:gen_function(v)
    dest_cpp = dest_cpp .. body
    dest_cpp = dest_cpp .. "\n\n"
    dest_hpp = dest_hpp .. ((had_errors and "//") or "") .. signature .. ";\n"
    if had_errors then n_err = n_err + 1 else n_success = n_success + 1 end
  end
end

print("Converted: ", n_success, " / ", n_success + n_err)
napi:print_missing_types()

return dest_cpp, dest_hpp, dest_js