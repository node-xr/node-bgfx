local idl = require("idl")
local util = require("util")
local napi = require("napi_gen")
local to_snake_case = util.to_snake_case

do
  local bgfx_idl, err = loadfile("bgfx.idl")
  print(bgfx_idl, err)
  setfenv(bgfx_idl, idl)
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

-- lets just print out enums for testing
for k, v in pairs(idl.types) do
  if v['enum'] then 
    --print(gen_enum(v))
    napi:add_enum_type(v.name .. "::Enum", v)
  elseif v.handle then
    napi:add_handle_type(v.name, v)
  end
end

for k, v in pairs(idl.funcs) do
  -- print(v.name, v.cname or "?")
  -- for k3, v3 in pairs(v) do print(k3, v3) end
  -- print(v.ret.fulltype)
  -- for i, v2 in ipairs(v.args) do
  --   print(v2.name, v2.fulltype, v2.default)
  --   -- for k3, v3 in pairs(v2) do
  --   --   print(k3, v3)
  --   -- end
  --   --print(i, v2)
  -- end
  if (not v.class) and (not v.cpponly) then
    print(napi:gen_function(v))
  end
end