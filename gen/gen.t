local idl = require("idl")
do
  local bgfx_idl, err = loadfile("bgfx.idl")
  print(bgfx_idl, err)
  setfenv(bgfx_idl, idl)
  bgfx_idl()
end

local function to_snake_case(s)
  local res = {}
  for v in s:gmatch "[%u%d]+%l*" do
    res[#res+1] = v:lower()
  end
  return table.concat(res, "_")
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
    print(gen_enum(v))
  end
end