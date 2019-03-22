-- napi_gen.t
local util = require("util")
local to_snake_case = util.to_snake_case

local NAPIFunction = {}
function NAPIFunction:init(gen, fdef)
  self.types = gen.types
  self.fdef = fdef
  self.stage_frags, self.call_args = {}, {}
  self.return_vals = {}
  self.had_errors = false
end

function NAPIFunction:gen_signature()
  local name = self.fdef.cname or to_snake_case(self.fdef.name):lower()
  return ("napi_value n_%s(napi_env env, napi_callback_info info)"):format(name)
end

function NAPIFunction:gen_call()
  local cname = "bgfx_" .. (self.fdef.cname or util.to_snake_case(self.fdef.name))
  local argstr = table.concat(self.call_args, ",")
  if self.fdef.ret.fulltype == "void" then
    return ("%s(%s);"):format(cname, argstr)
  else
    local t = self.types[self.fdef.ret.fulltype]
    table.insert(self.return_vals, 1, {"__ret", t})
    return ("%s __ret = %s(%s);"):format(self.fdef.ret.fulltype, cname, argstr)
  end
end

function NAPIFunction:gen_return()
  local return_frags = {}
  for idx, info in ipairs(self.return_vals) do
    local nidx = (#self.return_vals > 1) and idx
    if info[2] then
      local had_errors = false
      return_frags[idx], had_errors = info[2]:unstage(nidx, info[1])
      if had_errors then self.had_errors = true end
    else
      return_frags[idx] = "MISSING_RETURN;"
      self.had_errors = true
    end
  end
  return return_frags
end

function NAPIFunction:gen()
  local signature = self:gen_signature()
  local stage_frags = self.stage_frags
  local call_args = self.call_args
  local fdef = self.fdef
  local nargs = #(fdef.args)
  if nargs > 0 then
    stage_frags[#stage_frags+1] = {
      ("napi_value argv[%d];"):format(nargs),
      "size_t argc = 1;",
      "napi_get_cb_info(env, info, &argc, argv, NULL, NULL);",
      ("if (argc < %d) {"):format(nargs),
      '  napi_throw_error(env, "EINVAL", "Too few arguments");',
      "  return NULL;",
      "}"
    }
  end
  for argidx, arg in ipairs(fdef.args) do
    local t = self.types[arg.fulltype]
    if t then
      local argname, stagecall = t:stage(arg.name, arg.fulltype, argidx-1)
      call_args[#call_args+1] = argname
      stage_frags[#stage_frags+1] = stagecall
      if t.mutates then
        self.return_vals[#(self.return_vals)+1] = {argname, t}
      end
    else
      self.had_errors = true
      call_args[#call_args+1] = arg.name
      stage_frags[#stage_frags+1] = ("%s %s = MISSING_TYPE<%s>;"):format(
        arg.fulltype, arg.name, arg.fulltype
      )
    end
  end
  local call_frags = self:gen_call()
  local return_frags = self:gen_return()

  local body = util.flatten{stage_frags, call_frags, return_frags}
  local frags = util.flatten{signature .. "{", util.indent(body), "}"}
  if self.had_errors then frags = util.comment_out(frags) end
  return signature, table.concat(frags, "\n"), self.had_errors
end

local HandleType = {}
function HandleType:init(tdef)
  self.ctype = "bgfx_" .. to_snake_case(tdef.name):lower() .. "_t"
end

function HandleType:stage(argname, argtype, argidx)
  local frags = {
    ("%s %s;"):format(self.ctype, argname),
    "{",
    "  int32_t temp = 0;",
    ("  auto status = napi_get_value_int32(env, argv[%d], &temp);"):format(argidx),
    "  if(status != napi_ok){",
    '    napi_throw_error(env, "EINVAL", "Argument Error");',
    '     return NULL;',
    "  }",
    ("  %s.idx = (uint16_t)temp;"):format(argname),
    "}"
  }
  return argname, frags
end

function HandleType:unstage(idx, varname)
  return {}, true
end

local NumericType = {}
local NUMERIC_V8_READERS = {
  int32_t = "napi_get_value_int32",
  int64_t = "napi_get_value_int64",
  bool = "napi_get_value_bool",
  double = "napi_get_value_double"
}

function NumericType:init(final_type, v8_type)
  self.rfunc = NUMERIC_V8_READERS[v8_type]
  self.ttype = v8_type
  self.ctype = final_type
end

function NumericType:stage(argname, argtype, argidx)
  local frags = {
    ("%s %s;"):format(self.ctype, argname),
    "{",
    ("  %s temp = (%s)0;"):format(self.ttype, self.ttype),
    ("  auto status = %s(env, argv[%d], &temp);"):format(self.rfunc, argidx),
    "  if(status != napi_ok){",
    '    napi_throw_error(env, "EINVAL", "Argument Error");',
    '     return NULL;',
    "  }",
    ("  %s = (%s)temp;"):format(argname, self.ctype),
    "}"
  }
  return argname, frags
end

function NumericType:unstage(idx, varname)
  return {}, true
end

local EnumType = {}
function EnumType:init(tdef)
  self.ctype = "bgfx_" .. to_snake_case(tdef.name):lower() .. "_t"
  self.rfunc = NUMERIC_V8_READERS.int32_t
  self.ttype = 'int32_t'
end
EnumType.stage = NumericType.stage
EnumType.unstage = NumericType.unstage

local function new(proto, ...)
  local ret = setmetatable({}, {__index = proto})
  ret:init(...)
  return ret
end

local NAPIGen = {types = {}}
local numeric_types = {
  bool = 'bool',
  char = 'int32_t',
  float = 'double',
  int8_t = 'int32_t',
  int32_t = 'int32_t',
  int64_t = 'int64_t',
  uint8_t = 'int32_t',
  uint16_t = 'int32_t',
  uint32_t = 'int32_t',
  uint64_t = 'int64_t'
}
for final_type, v8_type in pairs(numeric_types) do
  NAPIGen.types[final_type] = new(NumericType, final_type, v8_type)
end
NAPIGen.types["ViewId"] = new(NumericType, "bgfx_view_id_t", "int32_t")

function NAPIGen:add_handle_type(name, t)
  self.types[name] = new(HandleType, t)
end

function NAPIGen:add_enum_type(name, t)
  self.types[name] = new(EnumType, t)
end

function NAPIGen:add_type(t)
  -- TODO
end

function NAPIGen:gen_function(fdef)
  local fgen = new(NAPIFunction, self, fdef)
  return fgen:gen()
end

return NAPIGen