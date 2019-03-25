-- napi_gen.t
local util = require("./gen/util")
local to_snake_case = util.to_snake_case
local unpack = table.unpack

local NAPIFunction = {}
function NAPIFunction:init(gen, fdef)
  self.types = gen.types
  self.missing_types = gen.missing_types
  self.fdef = fdef
  self.stage_frags, self.call_args = {}, {}
  self.return_vals = {}
  self.had_errors = false
end

function NAPIFunction:gen_signature()
  local name = self.fdef.cname or to_snake_case(self.fdef.name):lower()
  return ("napi_value nbgfx_%s(napi_env env, napi_callback_info info)"):format(name)
end

function NAPIFunction:gen_call()
  local cname = "bgfx_" .. (self.fdef.cname or util.to_snake_case(self.fdef.name))
  local argstr = table.concat(self.call_args, ", ")
  if self.fdef.ret.fulltype == "void" then
    return ("%s(%s);"):format(cname, argstr)
  else
    local t = self.types[self.fdef.ret.fulltype]
    table.insert(self.return_vals, 1, {"_ret", t})
    if t then
      return ("%s _ret = %s(%s);"):format(t.ctype, cname, argstr)
    end
  end
end

function NAPIFunction:gen_return()
  if #(self.return_vals) == 0 then
    return {"return NULL;"}
  end
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
      ("GET_ARGS(%d)"):format(nargs)
    }
  end
  for argidx, arg in ipairs(fdef.args) do
    local t = self.types[arg.fulltype]
    if t then
      local argname, stagecall = t:stage("arg" .. arg.name, arg.fulltype, argidx-1)
      call_args[#call_args+1] = argname
      stage_frags[#stage_frags+1] = stagecall
      if t.mutates then
        self.return_vals[#(self.return_vals)+1] = {argname, t}
      end
    else
      self.missing_types[arg.fulltype] = (self.missing_types[arg.fulltype] or 0) + 1
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

local function CHECK_STATUS(fcall, etype, emessage, indent)
  return util.indent({("ASSERT_OK(%s, \"%s\", \"%s\");"):format(
    fcall, etype or 'EINVAL', emessage or 'Unknown Error.')}, indent)
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
    CHECK_STATUS(("napi_get_value_int32(env, argv[%d], &temp)"):format(argidx)),
    ("  %s.idx = (uint16_t)temp;"):format(argname),
    "}"
  }
  return argname, frags
end

function HandleType:unstage(idx, varname)
  if not idx then -- we are the only return value
    local callstr = "napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret)"
    return {
      "napi_value _napi_ret;",
      "{",
      CHECK_STATUS(callstr, 'EINVAL', 'Return type error somehow?!'),
      "}",
      "return _napi_ret;"
    }
  else
    return ("MISSING_RETURN<%s>"):format(self.ctype), true
  end
end

local NumericType = {}
local NUMERIC_V8_CONVERSIONS = {
  int32_t = {"napi_get_value_int32", "napi_create_int32"},
  int64_t = {"napi_get_value_int64", "napi_create_int64"},
  bool = {"napi_get_value_bool", "napi_get_boolean"},
  double = {"napi_get_value_double", "napi_create_double"}
}

function NumericType:init(final_type, v8_type)
  self.rfunc, self.wfunc = unpack(NUMERIC_V8_CONVERSIONS[v8_type])
  self.ttype = v8_type
  self.ctype = final_type
end

function NumericType:stage(argname, argtype, argidx)
  local frags = {
    ("%s %s;"):format(self.ctype, argname),
    "{",
    ("  %s temp = (%s)0;"):format(self.ttype, self.ttype),
    CHECK_STATUS(("%s(env, argv[%d], &temp)"):format(self.rfunc, argidx)),
    ("  %s = (%s)temp;"):format(argname, self.ctype),
    "}"
  }
  return argname, frags
end

--napi_status napi_create_int32(napi_env env, int32_t value, napi_value* result)

function NumericType:unstage(idx, varname)
  if not idx then -- we are the only return value
    local callstr = ("%s(env, (%s)_ret, &_napi_ret)"):format(self.wfunc, self.ttype) 
    return {
      "napi_value _napi_ret;",
      CHECK_STATUS(callstr, 'EINVAL', 'Return type error somehow?!', 0),
      "return _napi_ret;"
    }
  else
    return ("MISSING_RETURN<%s>"):format(self.ctype), true
  end
end

local EnumType = {}
function EnumType:init(tdef)
  self.ctype = "bgfx_" .. to_snake_case(tdef.name):lower() .. "_t"
  self.rfunc, self.wfunc = unpack(NUMERIC_V8_CONVERSIONS.int32_t)
  self.ttype = 'int32_t'
end
EnumType.stage = NumericType.stage
EnumType.unstage = NumericType.unstage

local function new(proto, ...)
  local ret = setmetatable({}, {__index = proto})
  ret:init(...)
  return ret
end

local MemoryCopyType = {}
function MemoryCopyType:init()
  -- Nothing to do
  self.ctype = "const bgfx_memory_t*"
end
function MemoryCopyType:stage(argname, argtype, argidx)
  local tempname = "_ptr_" .. argidx
  local tempsize = "_size_" .. argidx
  local callstr = ("napi_get_arraybuffer_info(env, argv[%d], &%s, &%s)"):format(argidx, tempname, tempsize)
  return argname, {
    ("size_t %s = 0;"):format(tempsize),
    ("void* %s = NULL;"):format(tempname),
    "{",
    CHECK_STATUS(callstr),
    "}",
    ("const bgfx_memory_t* %s = bgfx_copy(%s, %s);"):format(argname, tempname, tempsize)
  }
end
function MemoryCopyType:unstage(idx, varname)
  return "MISSING_RETURN<const Memory*>", true
end

local VoidPointerType = {}
function VoidPointerType:init()
  self.ctype = "void*"
end
function VoidPointerType:stage(argname, argtype, argidx)
  local tempsize = "_size_" .. argidx
  local callstr = ("napi_get_arraybuffer_info(env, argv[%d], &%s, &%s)"):format(argidx, argname, tempsize)
  return argname, {
    ("size_t %s = 0;"):format(tempsize),
    ("void* %s = NULL;"):format(argname),
    "{",
    CHECK_STATUS(callstr),
    "}"
  }
end
function VoidPointerType:unstage(idx, varname)
  return "MISSING_RETURN<void*>", true
end

local OpaqueType = {}
function OpaqueType:init(ctype)
  self.ctype = ctype
end
function OpaqueType:stage(argname, argtype, argidx)
  local callstr = ("napi_get_value_external(env, argv[%d], (void **)&%s)"):format(argidx, argname)
  return argname, {
    ("%s %s = NULL;"):format(self.ctype, argname),
    "{",
    CHECK_STATUS(callstr),
    "}"
  }
end
function OpaqueType:unstage(idx, varname)
  if not idx then -- we are the only return value
    local callstr = ("%s(env, (%s)_ret, &_napi_ret)"):format(self.wfunc, self.ttype) 
    return {
      "napi_value _napi_ret;",
      CHECK_STATUS(callstr, 'EINVAL', 'Return type error somehow?!', 0),
      "return _napi_ret;"
    }
  else
    return ("MISSING_RETURN<%s>"):format(self.ctype), true
  end
end

local UTF8StringType = {}
function UTF8StringType:init()
  self.ctype = "const char*"
end
function UTF8StringType:stage(argname, argtype, argidx)
  local sizevar = ("_temp_size_%d"):format(argidx)
  local outsize = ("_temp_size_out_%d"):format(argidx)
  local callstr = ("napi_get_value_string_utf8(env, argv[%d], %s, %s, &%s)"):format(argidx, argname, sizevar, outsize)
  return argname, {
    ("char %s[2048];"):format(argname),
    ("size_t %s = 2048;"):format(sizevar),
    ("size_t %s;"):format(outsize),
    "{",
    CHECK_STATUS(callstr),
    "}"
  }
end
-- napi_status napi_create_string_utf8(napi_env env,
--                                     const char* str,
--                                     size_t length,
--                                     napi_value* result)
function UTF8StringType:unstage(idx, varname)
  if not idx then -- we are the only return value
    return {
      "napi_value _napi_ret;",
      "{",
      CHECK_STATUS("napi_create_string_utf8(env, _ret, strlen(_ret), &_napi_ret)"),
      "}",
      "return _napi_ret;"
    }
  else
    return ("MISSING_RETURN<%s>"):format(self.ctype), true
  end
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
NAPIGen.types["const Memory*"] = new(MemoryCopyType)
NAPIGen.types["void*"] = new(VoidPointerType)
NAPIGen.types["const void*"] = new(VoidPointerType)
NAPIGen.types["const VertexDecl &"] = new(OpaqueType, "bgfx_vertex_decl_t*")
NAPIGen.types["const VertexDecl&"] = new(OpaqueType, "bgfx_vertex_decl_t*")
NAPIGen.types["const PlatformData &"] = new(OpaqueType, "bgfx_platform_data_t*")
NAPIGen.types["const char*"] = new(UTF8StringType)

function NAPIGen:add_handle_type(name, t)
  self.types[name] = new(HandleType, t)
  self.missing_types = {}
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

function NAPIGen:print_missing_types()
  local tlist = {}
  for tname, missing_count in pairs(self.missing_types) do
    tlist[#tlist + 1] = {tname, missing_count}
  end
  table.sort(tlist, function(a, b) return a[2] > b[2] end)
  for _, p in ipairs(tlist) do
    print(unpack(p))
  end
end

return NAPIGen