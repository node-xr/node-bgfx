local funcs = {}

local function ad_hoc_function(options)
  local def = {}
  def.ret = {
    fulltype = options.return_type or "void"
  }
  def.args = {}
  for idx, arg in ipairs(options.args or {}) do
    def.args[idx] = {
      name = arg[1], fulltype = arg[2]
    }
  end
  def.cname = options.name
  def.body = options.body
  funcs[#funcs+1] = def
end

local function add(target)
  for _, def in ipairs(funcs) do
    target[#target+1] = def
  end
end

ad_hoc_function{
  name = "alloc_vertex_decl",
  args = {},
  return_type = "VertexDecl*",
  body = "bgfx_vertex_decl_t* _ret = new bgfx_vertex_decl_t;"
}

ad_hoc_function{
  name = "release_vertex_decl",
  args = {{"_decl", "VertexDecl*"}},
  return_type = "void",
  body = "delete arg_decl;"
}

ad_hoc_function{
  name = "init_minimal",
  args = {
    {"_ndt", "External*"}, 
    {"_nwh", "External*"}, 
    {"_width", "uint32_t"}, 
    {"_height", "uint32_t"}, 
    {"_reset", "uint32_t"}
  },
  return_type = "bool",
  body = [[
bgfx_init_t init;
  bgfx_init_ctor(&init);
  init.platformData.ndt = arg_ndt;
  init.platformData.nwh = arg_nwh;
  init.resolution.width = arg_width;
  init.resolution.height = arg_height;
  init.resolution.reset = arg_reset;
  bool _ret = bgfx_init(&init);]]
}

ad_hoc_function{
  name = "dbg_text_print",
  args = {
	  {"_x", "uint16_t"},
	  {"_y", "uint16_t"},
    {"_attr", "uint8_t"},
    {"_text", "const char*"},
  },
  return_type = "void",
  body = 'bgfx_dbg_text_printf(arg_x, arg_y, arg_attr, "%s", arg_text);'
}

return {add = add, funcs = funcs}