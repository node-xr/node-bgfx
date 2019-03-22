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
  local name = to_snake_case(self.fdef.cname or self.fdef.name):lower()
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
    if info[2] then
      return_frags[idx] = info[2]:unstage(idx, info[1])
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
  for argidx, arg in ipairs(fdef.args) do
    local t = self.types[arg.fulltype]
    if t then
      local argname, stagecall = t:stage(arg.name, arg.fulltype, argidx)
      call_args[#call_args+1] = argname
      stage_frags[#stage_frags+1] = stagecall
      if t:mutates() then
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
  stage_frags = util.concat(stage_frags)
  local call_frags = self:gen_call()
  local return_frags = self:gen_return()

  local body = util.concat{stage_frags, call_frags, return_frags}
  local frags = util.concat{signature .. "{", util.indent(body), "}"}
  if self.had_errors then frags = util.comment_out(frags) end
  return signature, table.concat(frags, "\n"), self.had_errors
end

local function new(proto, ...)
  local ret = setmetatable({}, {__index = proto})
  ret:init(...)
  return ret
end


local NAPIGen = {types = {}}
function NAPIGen:add_type(t)
  -- TODO
end

function NAPIGen:gen_function(fdef)
  local fgen = new(NAPIFunction, self, fdef)
  return fgen:gen()
end

return NAPIGen