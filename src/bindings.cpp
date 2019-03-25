//napi_value nbgfx_vertex_pack(napi_env env, napi_callback_info info){
//  napi_value argv[6];
//  GET_ARGS(6)
//  const float[4] _input = MISSING_TYPE<const float[4]>;
//  bool arg_inputNormalized;
//  {
//    bool temp = (bool)0;
//    ASSERT_OK(napi_get_value_bool(env, argv[1], &temp))
//    arg_inputNormalized = (bool)temp;
//  }
//  bgfx_attrib_t arg_attr;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
//    arg_attr = (bgfx_attrib_t)temp;
//  }
//  bgfx_vertex_decl_t* arg_decl = NULL;
//  {
//    ASSERT_OK(napi_get_value_external(env, argv[3], &arg_decl))
//  }
//  uint32_t _size_4 = 0;
//  void* arg_data = NULL;
//  {
//    ASSERT_OK(napi_get_arraybuffer_info(env, argv[4], &arg_data, &_size_4))
//  }
//  uint32_t arg_index;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[5], &temp))
//    arg_index = (uint32_t)temp;
//  }
//  bgfx_vertex_pack(_input, arg_inputNormalized, arg_attr, arg_decl, arg_data, arg_index);
//  return NULL;
//}

//napi_value nbgfx_vertex_unpack(napi_env env, napi_callback_info info){
//  napi_value argv[5];
//  GET_ARGS(5)
//  float[4] _output = MISSING_TYPE<float[4]>;
//  bgfx_attrib_t arg_attr;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_attr = (bgfx_attrib_t)temp;
//  }
//  bgfx_vertex_decl_t* arg_decl = NULL;
//  {
//    ASSERT_OK(napi_get_value_external(env, argv[2], &arg_decl))
//  }
//  uint32_t _size_3 = 0;
//  void* arg_data = NULL;
//  {
//    ASSERT_OK(napi_get_arraybuffer_info(env, argv[3], &arg_data, &_size_3))
//  }
//  uint32_t arg_index;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
//    arg_index = (uint32_t)temp;
//  }
//  bgfx_vertex_unpack(_output, arg_attr, arg_decl, arg_data, arg_index);
//  return NULL;
//}

napi_value nbgfx_vertex_convert(napi_env env, napi_callback_info info){
  napi_value argv[5];
  GET_ARGS(5)
  bgfx_vertex_decl_t* arg_dstDecl = NULL;
  {
    ASSERT_OK(napi_get_value_external(env, argv[0], &arg_dstDecl))
  }
  uint32_t _size_1 = 0;
  void* arg_dstData = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[1], &arg_dstData, &_size_1))
  }
  bgfx_vertex_decl_t* arg_srcDecl = NULL;
  {
    ASSERT_OK(napi_get_value_external(env, argv[2], &arg_srcDecl))
  }
  uint32_t _size_3 = 0;
  void* arg_srcData = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[3], &arg_srcData, &_size_3))
  }
  uint32_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_num = (uint32_t)temp;
  }
  bgfx_vertex_convert(arg_dstDecl, arg_dstData, arg_srcDecl, arg_srcData, arg_num);
  return NULL;
}

//napi_value nbgfx_weld_vertices(napi_env env, napi_callback_info info){
//  napi_value argv[5];
//  GET_ARGS(5)
//  uint16_t* _output = MISSING_TYPE<uint16_t*>;
//  bgfx_vertex_decl_t* arg_decl = NULL;
//  {
//    ASSERT_OK(napi_get_value_external(env, argv[1], &arg_decl))
//  }
//  uint32_t _size_2 = 0;
//  void* arg_data = NULL;
//  {
//    ASSERT_OK(napi_get_arraybuffer_info(env, argv[2], &arg_data, &_size_2))
//  }
//  uint16_t arg_num;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
//    arg_num = (uint16_t)temp;
//  }
//  float arg_epsilon;
//  {
//    double temp = (double)0;
//    ASSERT_OK(napi_get_value_double(env, argv[4], &temp))
//    arg_epsilon = (float)temp;
//  }
//  uint16_t _ret = bgfx_weld_vertices(_output, arg_decl, arg_data, arg_num, arg_epsilon);
//  napi_value _napi_ret;
//  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
//  return _napi_ret;
//}

napi_value nbgfx_topology_convert(napi_env env, napi_callback_info info){
  napi_value argv[6];
  GET_ARGS(6)
  bgfx_topology_convert_t arg_conversion;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_conversion = (bgfx_topology_convert_t)temp;
  }
  uint32_t _size_1 = 0;
  void* arg_dst = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[1], &arg_dst, &_size_1))
  }
  uint32_t arg_dstSize;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_dstSize = (uint32_t)temp;
  }
  uint32_t _size_3 = 0;
  void* arg_indices = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[3], &arg_indices, &_size_3))
  }
  uint32_t arg_numIndices;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_numIndices = (uint32_t)temp;
  }
  bool arg_index32;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[5], &temp))
    arg_index32 = (bool)temp;
  }
  uint32_t _ret = bgfx_topology_convert(arg_conversion, arg_dst, arg_dstSize, arg_indices, arg_numIndices, arg_index32);
  napi_value _napi_ret;
  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
  return _napi_ret;
}

//napi_value nbgfx_topology_sort_tri_list(napi_env env, napi_callback_info info){
//  napi_value argv[10];
//  GET_ARGS(10)
//  bgfx_topology_sort_t arg_sort;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_sort = (bgfx_topology_sort_t)temp;
//  }
//  uint32_t _size_1 = 0;
//  void* arg_dst = NULL;
//  {
//    ASSERT_OK(napi_get_arraybuffer_info(env, argv[1], &arg_dst, &_size_1))
//  }
//  uint32_t arg_dstSize;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
//    arg_dstSize = (uint32_t)temp;
//  }
//  const float[3] _dir = MISSING_TYPE<const float[3]>;
//  const float[3] _pos = MISSING_TYPE<const float[3]>;
//  uint32_t _size_5 = 0;
//  void* arg_vertices = NULL;
//  {
//    ASSERT_OK(napi_get_arraybuffer_info(env, argv[5], &arg_vertices, &_size_5))
//  }
//  uint32_t arg_stride;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[6], &temp))
//    arg_stride = (uint32_t)temp;
//  }
//  uint32_t _size_7 = 0;
//  void* arg_indices = NULL;
//  {
//    ASSERT_OK(napi_get_arraybuffer_info(env, argv[7], &arg_indices, &_size_7))
//  }
//  uint32_t arg_numIndices;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[8], &temp))
//    arg_numIndices = (uint32_t)temp;
//  }
//  bool arg_index32;
//  {
//    bool temp = (bool)0;
//    ASSERT_OK(napi_get_value_bool(env, argv[9], &temp))
//    arg_index32 = (bool)temp;
//  }
//  bgfx_topology_sort_tri_list(arg_sort, arg_dst, arg_dstSize, _dir, _pos, arg_vertices, arg_stride, arg_indices, arg_numIndices, arg_index32);
//  return NULL;
//}

//napi_value nbgfx_get_supported_renderers(napi_env env, napi_callback_info info){
//  napi_value argv[2];
//  GET_ARGS(2)
//  uint8_t arg_max;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_max = (uint8_t)temp;
//  }
//  RendererType::Enum* _enum = MISSING_TYPE<RendererType::Enum*>;
//  uint8_t _ret = bgfx_get_supported_renderers(arg_max, _enum);
//  napi_value _napi_ret;
//  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
//  return _napi_ret;
//}

napi_value nbgfx_get_renderer_name(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_renderer_type_t arg_type;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_type = (bgfx_renderer_type_t)temp;
  }
  const char* _ret = bgfx_get_renderer_name(arg_type);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_string_utf8(env, _ret, strlen(_ret), &_napi_ret))
  }
  return _napi_ret;
}

//napi_value nbgfx_init_ctor(napi_env env, napi_callback_info info){
//  napi_value argv[1];
//  GET_ARGS(1)
//  Init* _init = MISSING_TYPE<Init*>;
//  bgfx_init_ctor(_init);
//  return NULL;
//}

//napi_value nbgfx_init(napi_env env, napi_callback_info info){
//  napi_value argv[1];
//  GET_ARGS(1)
//  const Init & _init = MISSING_TYPE<const Init &>;
//  bool _ret = bgfx_init(_init);
//  napi_value _napi_ret;
//  ASSERT_OK(WTF_WHERE_IS_CREATE_BOOL(env, (bool)_ret, &_napi_ret))
//  return _napi_ret;
//}

napi_value nbgfx_shutdown(napi_env env, napi_callback_info info){
  bgfx_shutdown();
  return NULL;
}

napi_value nbgfx_reset(napi_env env, napi_callback_info info){
  napi_value argv[4];
  GET_ARGS(4)
  uint32_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_width = (uint32_t)temp;
  }
  uint32_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_height = (uint32_t)temp;
  }
  uint32_t arg_flags;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_flags = (uint32_t)temp;
  }
  bgfx_texture_format_t arg_format;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_format = (bgfx_texture_format_t)temp;
  }
  bgfx_reset(arg_width, arg_height, arg_flags, arg_format);
  return NULL;
}

napi_value nbgfx_frame(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bool arg_capture;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[0], &temp))
    arg_capture = (bool)temp;
  }
  uint32_t _ret = bgfx_frame(arg_capture);
  napi_value _napi_ret;
  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
  return _napi_ret;
}

napi_value nbgfx_get_renderer_type(napi_env env, napi_callback_info info){
  bgfx_renderer_type_t _ret = bgfx_get_renderer_type();
  napi_value _napi_ret;
  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
  return _napi_ret;
}

//napi_value nbgfx_get_caps(napi_env env, napi_callback_info info){
//}

//napi_value nbgfx_get_stats(napi_env env, napi_callback_info info){
//}

//napi_value nbgfx_alloc(napi_env env, napi_callback_info info){
//  napi_value argv[1];
//  GET_ARGS(1)
//  uint32_t arg_size;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_size = (uint32_t)temp;
//  }
//  const bgfx_memory_t* _ret = bgfx_alloc(arg_size);
//  MISSING_RETURN<const Memory*>
//}

//napi_value nbgfx_copy(napi_env env, napi_callback_info info){
//  napi_value argv[2];
//  GET_ARGS(2)
//  uint32_t _size_0 = 0;
//  void* arg_data = NULL;
//  {
//    ASSERT_OK(napi_get_arraybuffer_info(env, argv[0], &arg_data, &_size_0))
//  }
//  uint32_t arg_size;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_size = (uint32_t)temp;
//  }
//  const bgfx_memory_t* _ret = bgfx_copy(arg_data, arg_size);
//  MISSING_RETURN<const Memory*>
//}

//napi_value nbgfx_make_ref(napi_env env, napi_callback_info info){
//  napi_value argv[2];
//  GET_ARGS(2)
//  uint32_t _size_0 = 0;
//  void* arg_data = NULL;
//  {
//    ASSERT_OK(napi_get_arraybuffer_info(env, argv[0], &arg_data, &_size_0))
//  }
//  uint32_t arg_size;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_size = (uint32_t)temp;
//  }
//  const bgfx_memory_t* _ret = bgfx_make_ref(arg_data, arg_size);
//  MISSING_RETURN<const Memory*>
//}

//napi_value nbgfx_make_ref_release(napi_env env, napi_callback_info info){
//  napi_value argv[4];
//  GET_ARGS(4)
//  uint32_t _size_0 = 0;
//  void* arg_data = NULL;
//  {
//    ASSERT_OK(napi_get_arraybuffer_info(env, argv[0], &arg_data, &_size_0))
//  }
//  uint32_t arg_size;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_size = (uint32_t)temp;
//  }
//  ReleaseFn _releaseFn = MISSING_TYPE<ReleaseFn>;
//  uint32_t _size_3 = 0;
//  void* arg_userData = NULL;
//  {
//    ASSERT_OK(napi_get_arraybuffer_info(env, argv[3], &arg_userData, &_size_3))
//  }
//  const bgfx_memory_t* _ret = bgfx_make_ref_release(arg_data, arg_size, _releaseFn, arg_userData);
//  MISSING_RETURN<const Memory*>
//}

napi_value nbgfx_set_debug(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  uint32_t arg_debug;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_debug = (uint32_t)temp;
  }
  bgfx_set_debug(arg_debug);
  return NULL;
}

napi_value nbgfx_dbg_text_clear(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  uint8_t arg_attr;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_attr = (uint8_t)temp;
  }
  bool arg_small;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[1], &temp))
    arg_small = (bool)temp;
  }
  bgfx_dbg_text_clear(arg_attr, arg_small);
  return NULL;
}

napi_value nbgfx_dbg_text_printf(napi_env env, napi_callback_info info){
  napi_value argv[4];
  GET_ARGS(4)
  uint16_t arg_x;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_x = (uint16_t)temp;
  }
  uint16_t arg_y;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_y = (uint16_t)temp;
  }
  uint8_t arg_attr;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_attr = (uint8_t)temp;
  }
  char* arg_format = magic_global_string_buffer;
  size_t _temp_size_3 = 0;
  size_t _temp_size_out_3 = 0;
  {
    ASSERT_OK(napi_get_value_string_utf8(env, argv[3], arg_format, _temp_size_3 &_temp_size_out_3))
  }
  bgfx_dbg_text_printf(arg_x, arg_y, arg_attr, arg_format);
  return NULL;
}

//napi_value nbgfx_dbg_text_vprintf(napi_env env, napi_callback_info info){
//  napi_value argv[5];
//  GET_ARGS(5)
//  uint16_t arg_x;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_x = (uint16_t)temp;
//  }
//  uint16_t arg_y;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_y = (uint16_t)temp;
//  }
//  uint8_t arg_attr;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
//    arg_attr = (uint8_t)temp;
//  }
//  char* arg_format = magic_global_string_buffer;
//  size_t _temp_size_3 = 0;
//  size_t _temp_size_out_3 = 0;
//  {
//    ASSERT_OK(napi_get_value_string_utf8(env, argv[3], arg_format, _temp_size_3 &_temp_size_out_3))
//  }
//  va_list _argList = MISSING_TYPE<va_list>;
//  bgfx_dbg_text_vprintf(arg_x, arg_y, arg_attr, arg_format, _argList);
//  return NULL;
//}

napi_value nbgfx_dbg_text_image(napi_env env, napi_callback_info info){
  napi_value argv[6];
  GET_ARGS(6)
  uint16_t arg_x;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_x = (uint16_t)temp;
  }
  uint16_t arg_y;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_y = (uint16_t)temp;
  }
  uint16_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_width = (uint16_t)temp;
  }
  uint16_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_height = (uint16_t)temp;
  }
  uint32_t _size_4 = 0;
  void* arg_data = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[4], &arg_data, &_size_4))
  }
  uint16_t arg_pitch;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[5], &temp))
    arg_pitch = (uint16_t)temp;
  }
  bgfx_dbg_text_image(arg_x, arg_y, arg_width, arg_height, arg_data, arg_pitch);
  return NULL;
}

napi_value nbgfx_create_index_buffer(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  uint32_t _size_0 = 0;
  void* _ptr_0 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[0], &_ptr_0, &_size_0))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_0, _size_0);
  uint16_t arg_flags;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_flags = (uint16_t)temp;
  }
  bgfx_index_buffer_handle_t _ret = bgfx_create_index_buffer(arg_mem, arg_flags);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_set_index_buffer_name(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_index_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  char* arg_name = magic_global_string_buffer;
  size_t _temp_size_1 = 0;
  size_t _temp_size_out_1 = 0;
  {
    ASSERT_OK(napi_get_value_string_utf8(env, argv[1], arg_name, _temp_size_1 &_temp_size_out_1))
  }
  int32_t arg_len;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_len = (int32_t)temp;
  }
  bgfx_set_index_buffer_name(arg_handle, arg_name, arg_len);
  return NULL;
}

napi_value nbgfx_destroy_index_buffer(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_index_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_destroy_index_buffer(arg_handle);
  return NULL;
}

napi_value nbgfx_create_vertex_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  uint32_t _size_0 = 0;
  void* _ptr_0 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[0], &_ptr_0, &_size_0))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_0, _size_0);
  bgfx_vertex_decl_t* arg_decl = NULL;
  {
    ASSERT_OK(napi_get_value_external(env, argv[1], &arg_decl))
  }
  uint16_t arg_flags;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_flags = (uint16_t)temp;
  }
  bgfx_vertex_buffer_handle_t _ret = bgfx_create_vertex_buffer(arg_mem, arg_decl, arg_flags);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_set_vertex_buffer_name(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_vertex_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  char* arg_name = magic_global_string_buffer;
  size_t _temp_size_1 = 0;
  size_t _temp_size_out_1 = 0;
  {
    ASSERT_OK(napi_get_value_string_utf8(env, argv[1], arg_name, _temp_size_1 &_temp_size_out_1))
  }
  int32_t arg_len;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_len = (int32_t)temp;
  }
  bgfx_set_vertex_buffer_name(arg_handle, arg_name, arg_len);
  return NULL;
}

napi_value nbgfx_destroy_vertex_buffer(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_vertex_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_destroy_vertex_buffer(arg_handle);
  return NULL;
}

napi_value nbgfx_create_dynamic_index_buffer(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  uint32_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_num = (uint32_t)temp;
  }
  uint16_t arg_flags;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_flags = (uint16_t)temp;
  }
  bgfx_dynamic_index_buffer_handle_t _ret = bgfx_create_dynamic_index_buffer(arg_num, arg_flags);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_create_dynamic_index_buffer_mem(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  uint32_t _size_0 = 0;
  void* _ptr_0 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[0], &_ptr_0, &_size_0))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_0, _size_0);
  uint16_t arg_flags;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_flags = (uint16_t)temp;
  }
  bgfx_dynamic_index_buffer_handle_t _ret = bgfx_create_dynamic_index_buffer_mem(arg_mem, arg_flags);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_update_dynamic_index_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_dynamic_index_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint32_t arg_startIndex;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_startIndex = (uint32_t)temp;
  }
  uint32_t _size_2 = 0;
  void* _ptr_2 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[2], &_ptr_2, &_size_2))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_2, _size_2);
  bgfx_update_dynamic_index_buffer(arg_handle, arg_startIndex, arg_mem);
  return NULL;
}

napi_value nbgfx_destroy_dynamic_index_buffer(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_dynamic_index_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_destroy_dynamic_index_buffer(arg_handle);
  return NULL;
}

napi_value nbgfx_create_dynamic_vertex_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  uint32_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_num = (uint32_t)temp;
  }
  bgfx_vertex_decl_t* arg_decl = NULL;
  {
    ASSERT_OK(napi_get_value_external(env, argv[1], &arg_decl))
  }
  uint16_t arg_flags;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_flags = (uint16_t)temp;
  }
  bgfx_dynamic_vertex_buffer_handle_t _ret = bgfx_create_dynamic_vertex_buffer(arg_num, arg_decl, arg_flags);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_create_dynamic_vertex_buffer_mem(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  uint32_t _size_0 = 0;
  void* _ptr_0 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[0], &_ptr_0, &_size_0))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_0, _size_0);
  bgfx_vertex_decl_t* arg_decl = NULL;
  {
    ASSERT_OK(napi_get_value_external(env, argv[1], &arg_decl))
  }
  uint16_t arg_flags;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_flags = (uint16_t)temp;
  }
  bgfx_dynamic_vertex_buffer_handle_t _ret = bgfx_create_dynamic_vertex_buffer_mem(arg_mem, arg_decl, arg_flags);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_update_dynamic_vertex_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_dynamic_vertex_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint32_t arg_startVertex;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_startVertex = (uint32_t)temp;
  }
  uint32_t _size_2 = 0;
  void* _ptr_2 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[2], &_ptr_2, &_size_2))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_2, _size_2);
  bgfx_update_dynamic_vertex_buffer(arg_handle, arg_startVertex, arg_mem);
  return NULL;
}

napi_value nbgfx_destroy_dynamic_vertex_buffer(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_dynamic_vertex_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_destroy_dynamic_vertex_buffer(arg_handle);
  return NULL;
}

napi_value nbgfx_get_avail_transient_index_buffer(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  uint32_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_num = (uint32_t)temp;
  }
  uint32_t _ret = bgfx_get_avail_transient_index_buffer(arg_num);
  napi_value _napi_ret;
  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
  return _napi_ret;
}

napi_value nbgfx_get_avail_transient_vertex_buffer(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  uint32_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_num = (uint32_t)temp;
  }
  bgfx_vertex_decl_t* arg_decl = NULL;
  {
    ASSERT_OK(napi_get_value_external(env, argv[1], &arg_decl))
  }
  uint32_t _ret = bgfx_get_avail_transient_vertex_buffer(arg_num, arg_decl);
  napi_value _napi_ret;
  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
  return _napi_ret;
}

napi_value nbgfx_get_avail_instance_data_buffer(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  uint32_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_num = (uint32_t)temp;
  }
  uint16_t arg_stride;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_stride = (uint16_t)temp;
  }
  uint32_t _ret = bgfx_get_avail_instance_data_buffer(arg_num, arg_stride);
  napi_value _napi_ret;
  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
  return _napi_ret;
}

//napi_value nbgfx_alloc_transient_index_buffer(napi_env env, napi_callback_info info){
//  napi_value argv[2];
//  GET_ARGS(2)
//  TransientIndexBuffer* _tib = MISSING_TYPE<TransientIndexBuffer*>;
//  uint32_t arg_num;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_num = (uint32_t)temp;
//  }
//  bgfx_alloc_transient_index_buffer(_tib, arg_num);
//  return NULL;
//}

//napi_value nbgfx_alloc_transient_vertex_buffer(napi_env env, napi_callback_info info){
//  napi_value argv[3];
//  GET_ARGS(3)
//  TransientVertexBuffer* _tvb = MISSING_TYPE<TransientVertexBuffer*>;
//  uint32_t arg_num;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_num = (uint32_t)temp;
//  }
//  bgfx_vertex_decl_t* arg_decl = NULL;
//  {
//    ASSERT_OK(napi_get_value_external(env, argv[2], &arg_decl))
//  }
//  bgfx_alloc_transient_vertex_buffer(_tvb, arg_num, arg_decl);
//  return NULL;
//}

//napi_value nbgfx_alloc_transient_buffers(napi_env env, napi_callback_info info){
//  napi_value argv[5];
//  GET_ARGS(5)
//  TransientVertexBuffer* _tvb = MISSING_TYPE<TransientVertexBuffer*>;
//  bgfx_vertex_decl_t* arg_decl = NULL;
//  {
//    ASSERT_OK(napi_get_value_external(env, argv[1], &arg_decl))
//  }
//  uint32_t arg_numVertices;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
//    arg_numVertices = (uint32_t)temp;
//  }
//  TransientIndexBuffer* _tib = MISSING_TYPE<TransientIndexBuffer*>;
//  uint32_t arg_numIndices;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
//    arg_numIndices = (uint32_t)temp;
//  }
//  bool _ret = bgfx_alloc_transient_buffers(_tvb, arg_decl, arg_numVertices, _tib, arg_numIndices);
//  napi_value _napi_ret;
//  ASSERT_OK(WTF_WHERE_IS_CREATE_BOOL(env, (bool)_ret, &_napi_ret))
//  return _napi_ret;
//}

//napi_value nbgfx_alloc_instance_data_buffer(napi_env env, napi_callback_info info){
//  napi_value argv[3];
//  GET_ARGS(3)
//  InstanceDataBuffer* _idb = MISSING_TYPE<InstanceDataBuffer*>;
//  uint32_t arg_num;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_num = (uint32_t)temp;
//  }
//  uint16_t arg_stride;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
//    arg_stride = (uint16_t)temp;
//  }
//  bgfx_alloc_instance_data_buffer(_idb, arg_num, arg_stride);
//  return NULL;
//}

napi_value nbgfx_create_indirect_buffer(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  uint32_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_num = (uint32_t)temp;
  }
  bgfx_indirect_buffer_handle_t _ret = bgfx_create_indirect_buffer(arg_num);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_destroy_indirect_buffer(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_indirect_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_destroy_indirect_buffer(arg_handle);
  return NULL;
}

napi_value nbgfx_create_shader(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  uint32_t _size_0 = 0;
  void* _ptr_0 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[0], &_ptr_0, &_size_0))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_0, _size_0);
  bgfx_shader_handle_t _ret = bgfx_create_shader(arg_mem);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

//napi_value nbgfx_get_shader_uniforms(napi_env env, napi_callback_info info){
//  napi_value argv[3];
//  GET_ARGS(3)
//  bgfx_shader_handle_t arg_handle;
//  {
//    int32_t temp = 0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_handle.idx = (uint16_t)temp;
//  }
//  UniformHandle* _uniforms = MISSING_TYPE<UniformHandle*>;
//  uint16_t arg_max;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
//    arg_max = (uint16_t)temp;
//  }
//  uint16_t _ret = bgfx_get_shader_uniforms(arg_handle, _uniforms, arg_max);
//  napi_value _napi_ret;
//  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
//  return _napi_ret;
//}

napi_value nbgfx_set_shader_name(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_shader_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  char* arg_name = magic_global_string_buffer;
  size_t _temp_size_1 = 0;
  size_t _temp_size_out_1 = 0;
  {
    ASSERT_OK(napi_get_value_string_utf8(env, argv[1], arg_name, _temp_size_1 &_temp_size_out_1))
  }
  int32_t arg_len;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_len = (int32_t)temp;
  }
  bgfx_set_shader_name(arg_handle, arg_name, arg_len);
  return NULL;
}

napi_value nbgfx_destroy_shader(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_shader_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_destroy_shader(arg_handle);
  return NULL;
}

napi_value nbgfx_create_program(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_shader_handle_t arg_vsh;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_vsh.idx = (uint16_t)temp;
  }
  bgfx_shader_handle_t arg_fsh;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_fsh.idx = (uint16_t)temp;
  }
  bool arg_destroyShaders;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[2], &temp))
    arg_destroyShaders = (bool)temp;
  }
  bgfx_program_handle_t _ret = bgfx_create_program(arg_vsh, arg_fsh, arg_destroyShaders);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_create_compute_program(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  bgfx_shader_handle_t arg_csh;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_csh.idx = (uint16_t)temp;
  }
  bool arg_destroyShaders;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[1], &temp))
    arg_destroyShaders = (bool)temp;
  }
  bgfx_program_handle_t _ret = bgfx_create_compute_program(arg_csh, arg_destroyShaders);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_destroy_program(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_program_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_destroy_program(arg_handle);
  return NULL;
}

napi_value nbgfx_is_texture_valid(napi_env env, napi_callback_info info){
  napi_value argv[5];
  GET_ARGS(5)
  uint16_t arg_depth;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_depth = (uint16_t)temp;
  }
  bool arg_cubeMap;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[1], &temp))
    arg_cubeMap = (bool)temp;
  }
  uint16_t arg_numLayers;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_numLayers = (uint16_t)temp;
  }
  bgfx_texture_format_t arg_format;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_format = (bgfx_texture_format_t)temp;
  }
  uint64_t arg_flags;
  {
    int64_t temp = (int64_t)0;
    ASSERT_OK(napi_get_value_int64(env, argv[4], &temp))
    arg_flags = (uint64_t)temp;
  }
  bool _ret = bgfx_is_texture_valid(arg_depth, arg_cubeMap, arg_numLayers, arg_format, arg_flags);
  napi_value _napi_ret;
  ASSERT_OK(WTF_WHERE_IS_CREATE_BOOL(env, (bool)_ret, &_napi_ret))
  return _napi_ret;
}

//napi_value nbgfx_calc_texture_size(napi_env env, napi_callback_info info){
//  napi_value argv[8];
//  GET_ARGS(8)
//  TextureInfo & _info = MISSING_TYPE<TextureInfo &>;
//  uint16_t arg_width;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_width = (uint16_t)temp;
//  }
//  uint16_t arg_height;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
//    arg_height = (uint16_t)temp;
//  }
//  uint16_t arg_depth;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
//    arg_depth = (uint16_t)temp;
//  }
//  bool arg_cubeMap;
//  {
//    bool temp = (bool)0;
//    ASSERT_OK(napi_get_value_bool(env, argv[4], &temp))
//    arg_cubeMap = (bool)temp;
//  }
//  bool arg_hasMips;
//  {
//    bool temp = (bool)0;
//    ASSERT_OK(napi_get_value_bool(env, argv[5], &temp))
//    arg_hasMips = (bool)temp;
//  }
//  uint16_t arg_numLayers;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[6], &temp))
//    arg_numLayers = (uint16_t)temp;
//  }
//  bgfx_texture_format_t arg_format;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[7], &temp))
//    arg_format = (bgfx_texture_format_t)temp;
//  }
//  bgfx_calc_texture_size(_info, arg_width, arg_height, arg_depth, arg_cubeMap, arg_hasMips, arg_numLayers, arg_format);
//  return NULL;
//}

//napi_value nbgfx_create_texture(napi_env env, napi_callback_info info){
//  napi_value argv[4];
//  GET_ARGS(4)
//  uint32_t _size_0 = 0;
//  void* _ptr_0 = NULL;
//  {
//    ASSERT_OK(napi_get_arraybuffer_info(env, argv[0], &_ptr_0, &_size_0))
//  }
//  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_0, _size_0);
//  uint64_t arg_flags;
//  {
//    int64_t temp = (int64_t)0;
//    ASSERT_OK(napi_get_value_int64(env, argv[1], &temp))
//    arg_flags = (uint64_t)temp;
//  }
//  uint8_t arg_skip;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
//    arg_skip = (uint8_t)temp;
//  }
//  TextureInfo* _info = MISSING_TYPE<TextureInfo*>;
//  bgfx_texture_handle_t _ret = bgfx_create_texture(arg_mem, arg_flags, arg_skip, _info);
//  napi_value _napi_ret;
//  {
//    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
//  }
//  return _napi_ret;
//}

napi_value nbgfx_create_texture_2d(napi_env env, napi_callback_info info){
  napi_value argv[7];
  GET_ARGS(7)
  uint16_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_width = (uint16_t)temp;
  }
  uint16_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_height = (uint16_t)temp;
  }
  bool arg_hasMips;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[2], &temp))
    arg_hasMips = (bool)temp;
  }
  uint16_t arg_numLayers;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_numLayers = (uint16_t)temp;
  }
  bgfx_texture_format_t arg_format;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_format = (bgfx_texture_format_t)temp;
  }
  uint64_t arg_flags;
  {
    int64_t temp = (int64_t)0;
    ASSERT_OK(napi_get_value_int64(env, argv[5], &temp))
    arg_flags = (uint64_t)temp;
  }
  uint32_t _size_6 = 0;
  void* _ptr_6 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[6], &_ptr_6, &_size_6))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_6, _size_6);
  bgfx_texture_handle_t _ret = bgfx_create_texture_2d(arg_width, arg_height, arg_hasMips, arg_numLayers, arg_format, arg_flags, arg_mem);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_create_texture_2d_scaled(napi_env env, napi_callback_info info){
  napi_value argv[5];
  GET_ARGS(5)
  bgfx_backbuffer_ratio_t arg_ratio;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_ratio = (bgfx_backbuffer_ratio_t)temp;
  }
  bool arg_hasMips;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[1], &temp))
    arg_hasMips = (bool)temp;
  }
  uint16_t arg_numLayers;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_numLayers = (uint16_t)temp;
  }
  bgfx_texture_format_t arg_format;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_format = (bgfx_texture_format_t)temp;
  }
  uint64_t arg_flags;
  {
    int64_t temp = (int64_t)0;
    ASSERT_OK(napi_get_value_int64(env, argv[4], &temp))
    arg_flags = (uint64_t)temp;
  }
  bgfx_texture_handle_t _ret = bgfx_create_texture_2d_scaled(arg_ratio, arg_hasMips, arg_numLayers, arg_format, arg_flags);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_create_texture_3d(napi_env env, napi_callback_info info){
  napi_value argv[7];
  GET_ARGS(7)
  uint16_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_width = (uint16_t)temp;
  }
  uint16_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_height = (uint16_t)temp;
  }
  uint16_t arg_depth;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_depth = (uint16_t)temp;
  }
  bool arg_hasMips;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[3], &temp))
    arg_hasMips = (bool)temp;
  }
  bgfx_texture_format_t arg_format;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_format = (bgfx_texture_format_t)temp;
  }
  uint64_t arg_flags;
  {
    int64_t temp = (int64_t)0;
    ASSERT_OK(napi_get_value_int64(env, argv[5], &temp))
    arg_flags = (uint64_t)temp;
  }
  uint32_t _size_6 = 0;
  void* _ptr_6 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[6], &_ptr_6, &_size_6))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_6, _size_6);
  bgfx_texture_handle_t _ret = bgfx_create_texture_3d(arg_width, arg_height, arg_depth, arg_hasMips, arg_format, arg_flags, arg_mem);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_create_texture_cube(napi_env env, napi_callback_info info){
  napi_value argv[6];
  GET_ARGS(6)
  uint16_t arg_size;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_size = (uint16_t)temp;
  }
  bool arg_hasMips;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[1], &temp))
    arg_hasMips = (bool)temp;
  }
  uint16_t arg_numLayers;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_numLayers = (uint16_t)temp;
  }
  bgfx_texture_format_t arg_format;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_format = (bgfx_texture_format_t)temp;
  }
  uint64_t arg_flags;
  {
    int64_t temp = (int64_t)0;
    ASSERT_OK(napi_get_value_int64(env, argv[4], &temp))
    arg_flags = (uint64_t)temp;
  }
  uint32_t _size_5 = 0;
  void* _ptr_5 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[5], &_ptr_5, &_size_5))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_5, _size_5);
  bgfx_texture_handle_t _ret = bgfx_create_texture_cube(arg_size, arg_hasMips, arg_numLayers, arg_format, arg_flags, arg_mem);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_update_texture_2d(napi_env env, napi_callback_info info){
  napi_value argv[9];
  GET_ARGS(9)
  bgfx_texture_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint16_t arg_layer;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_layer = (uint16_t)temp;
  }
  uint8_t arg_mip;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_mip = (uint8_t)temp;
  }
  uint16_t arg_x;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_x = (uint16_t)temp;
  }
  uint16_t arg_y;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_y = (uint16_t)temp;
  }
  uint16_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[5], &temp))
    arg_width = (uint16_t)temp;
  }
  uint16_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[6], &temp))
    arg_height = (uint16_t)temp;
  }
  uint32_t _size_7 = 0;
  void* _ptr_7 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[7], &_ptr_7, &_size_7))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_7, _size_7);
  uint16_t arg_pitch;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[8], &temp))
    arg_pitch = (uint16_t)temp;
  }
  bgfx_update_texture_2d(arg_handle, arg_layer, arg_mip, arg_x, arg_y, arg_width, arg_height, arg_mem, arg_pitch);
  return NULL;
}

napi_value nbgfx_update_texture_3d(napi_env env, napi_callback_info info){
  napi_value argv[9];
  GET_ARGS(9)
  bgfx_texture_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint8_t arg_mip;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_mip = (uint8_t)temp;
  }
  uint16_t arg_x;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_x = (uint16_t)temp;
  }
  uint16_t arg_y;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_y = (uint16_t)temp;
  }
  uint16_t arg_z;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_z = (uint16_t)temp;
  }
  uint16_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[5], &temp))
    arg_width = (uint16_t)temp;
  }
  uint16_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[6], &temp))
    arg_height = (uint16_t)temp;
  }
  uint16_t arg_depth;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[7], &temp))
    arg_depth = (uint16_t)temp;
  }
  uint32_t _size_8 = 0;
  void* _ptr_8 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[8], &_ptr_8, &_size_8))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_8, _size_8);
  bgfx_update_texture_3d(arg_handle, arg_mip, arg_x, arg_y, arg_z, arg_width, arg_height, arg_depth, arg_mem);
  return NULL;
}

napi_value nbgfx_update_texture_cube(napi_env env, napi_callback_info info){
  napi_value argv[10];
  GET_ARGS(10)
  bgfx_texture_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint16_t arg_layer;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_layer = (uint16_t)temp;
  }
  uint8_t arg_side;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_side = (uint8_t)temp;
  }
  uint8_t arg_mip;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_mip = (uint8_t)temp;
  }
  uint16_t arg_x;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_x = (uint16_t)temp;
  }
  uint16_t arg_y;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[5], &temp))
    arg_y = (uint16_t)temp;
  }
  uint16_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[6], &temp))
    arg_width = (uint16_t)temp;
  }
  uint16_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[7], &temp))
    arg_height = (uint16_t)temp;
  }
  uint32_t _size_8 = 0;
  void* _ptr_8 = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[8], &_ptr_8, &_size_8))
  }
  const bgfx_memory_t* arg_mem = bgfx_copy(_ptr_8, _size_8);
  uint16_t arg_pitch;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[9], &temp))
    arg_pitch = (uint16_t)temp;
  }
  bgfx_update_texture_cube(arg_handle, arg_layer, arg_side, arg_mip, arg_x, arg_y, arg_width, arg_height, arg_mem, arg_pitch);
  return NULL;
}

napi_value nbgfx_read_texture(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_texture_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint32_t _size_1 = 0;
  void* arg_data = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[1], &arg_data, &_size_1))
  }
  uint8_t arg_mip;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_mip = (uint8_t)temp;
  }
  uint32_t _ret = bgfx_read_texture(arg_handle, arg_data, arg_mip);
  napi_value _napi_ret;
  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
  return _napi_ret;
}

napi_value nbgfx_set_texture_name(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_texture_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  char* arg_name = magic_global_string_buffer;
  size_t _temp_size_1 = 0;
  size_t _temp_size_out_1 = 0;
  {
    ASSERT_OK(napi_get_value_string_utf8(env, argv[1], arg_name, _temp_size_1 &_temp_size_out_1))
  }
  int32_t arg_len;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_len = (int32_t)temp;
  }
  bgfx_set_texture_name(arg_handle, arg_name, arg_len);
  return NULL;
}

//napi_value nbgfx_get_direct_access_ptr(napi_env env, napi_callback_info info){
//  napi_value argv[1];
//  GET_ARGS(1)
//  bgfx_texture_handle_t arg_handle;
//  {
//    int32_t temp = 0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_handle.idx = (uint16_t)temp;
//  }
//  void* _ret = bgfx_get_direct_access_ptr(arg_handle);
//  MISSING_RETURN<void*>
//}

napi_value nbgfx_destroy_texture(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_texture_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_destroy_texture(arg_handle);
  return NULL;
}

napi_value nbgfx_create_frame_buffer(napi_env env, napi_callback_info info){
  napi_value argv[4];
  GET_ARGS(4)
  uint16_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_width = (uint16_t)temp;
  }
  uint16_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_height = (uint16_t)temp;
  }
  bgfx_texture_format_t arg_format;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_format = (bgfx_texture_format_t)temp;
  }
  uint64_t arg_textureFlags;
  {
    int64_t temp = (int64_t)0;
    ASSERT_OK(napi_get_value_int64(env, argv[3], &temp))
    arg_textureFlags = (uint64_t)temp;
  }
  bgfx_frame_buffer_handle_t _ret = bgfx_create_frame_buffer(arg_width, arg_height, arg_format, arg_textureFlags);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_create_frame_buffer_scaled(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_backbuffer_ratio_t arg_ratio;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_ratio = (bgfx_backbuffer_ratio_t)temp;
  }
  bgfx_texture_format_t arg_format;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_format = (bgfx_texture_format_t)temp;
  }
  uint64_t arg_textureFlags;
  {
    int64_t temp = (int64_t)0;
    ASSERT_OK(napi_get_value_int64(env, argv[2], &temp))
    arg_textureFlags = (uint64_t)temp;
  }
  bgfx_frame_buffer_handle_t _ret = bgfx_create_frame_buffer_scaled(arg_ratio, arg_format, arg_textureFlags);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

//napi_value nbgfx_create_frame_buffer_from_handles(napi_env env, napi_callback_info info){
//  napi_value argv[3];
//  GET_ARGS(3)
//  uint8_t arg_num;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_num = (uint8_t)temp;
//  }
//  const TextureHandle* _handles = MISSING_TYPE<const TextureHandle*>;
//  bool arg_destroyTexture;
//  {
//    bool temp = (bool)0;
//    ASSERT_OK(napi_get_value_bool(env, argv[2], &temp))
//    arg_destroyTexture = (bool)temp;
//  }
//  bgfx_frame_buffer_handle_t _ret = bgfx_create_frame_buffer_from_handles(arg_num, _handles, arg_destroyTexture);
//  napi_value _napi_ret;
//  {
//    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
//  }
//  return _napi_ret;
//}

//napi_value nbgfx_create_frame_buffer_from_attachment(napi_env env, napi_callback_info info){
//  napi_value argv[3];
//  GET_ARGS(3)
//  uint8_t arg_num;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_num = (uint8_t)temp;
//  }
//  const Attachment* _attachment = MISSING_TYPE<const Attachment*>;
//  bool arg_destroyTexture;
//  {
//    bool temp = (bool)0;
//    ASSERT_OK(napi_get_value_bool(env, argv[2], &temp))
//    arg_destroyTexture = (bool)temp;
//  }
//  bgfx_frame_buffer_handle_t _ret = bgfx_create_frame_buffer_from_attachment(arg_num, _attachment, arg_destroyTexture);
//  napi_value _napi_ret;
//  {
//    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
//  }
//  return _napi_ret;
//}

napi_value nbgfx_create_frame_buffer_from_nwh(napi_env env, napi_callback_info info){
  napi_value argv[5];
  GET_ARGS(5)
  uint32_t _size_0 = 0;
  void* arg_nwh = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[0], &arg_nwh, &_size_0))
  }
  uint16_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_width = (uint16_t)temp;
  }
  uint16_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_height = (uint16_t)temp;
  }
  bgfx_texture_format_t arg_format;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_format = (bgfx_texture_format_t)temp;
  }
  bgfx_texture_format_t arg_depthFormat;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_depthFormat = (bgfx_texture_format_t)temp;
  }
  bgfx_frame_buffer_handle_t _ret = bgfx_create_frame_buffer_from_nwh(arg_nwh, arg_width, arg_height, arg_format, arg_depthFormat);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_set_frame_buffer_name(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_frame_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  char* arg_name = magic_global_string_buffer;
  size_t _temp_size_1 = 0;
  size_t _temp_size_out_1 = 0;
  {
    ASSERT_OK(napi_get_value_string_utf8(env, argv[1], arg_name, _temp_size_1 &_temp_size_out_1))
  }
  int32_t arg_len;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_len = (int32_t)temp;
  }
  bgfx_set_frame_buffer_name(arg_handle, arg_name, arg_len);
  return NULL;
}

napi_value nbgfx_get_texture(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  bgfx_frame_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint8_t arg_attachment;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_attachment = (uint8_t)temp;
  }
  bgfx_texture_handle_t _ret = bgfx_get_texture(arg_handle, arg_attachment);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

napi_value nbgfx_destroy_frame_buffer(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_frame_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_destroy_frame_buffer(arg_handle);
  return NULL;
}

napi_value nbgfx_create_uniform(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  char* arg_name = magic_global_string_buffer;
  size_t _temp_size_0 = 0;
  size_t _temp_size_out_0 = 0;
  {
    ASSERT_OK(napi_get_value_string_utf8(env, argv[0], arg_name, _temp_size_0 &_temp_size_out_0))
  }
  bgfx_uniform_type_t arg_type;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_type = (bgfx_uniform_type_t)temp;
  }
  uint16_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_num = (uint16_t)temp;
  }
  bgfx_uniform_handle_t _ret = bgfx_create_uniform(arg_name, arg_type, arg_num);
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

//napi_value nbgfx_get_uniform_info(napi_env env, napi_callback_info info){
//  napi_value argv[2];
//  GET_ARGS(2)
//  bgfx_uniform_handle_t arg_handle;
//  {
//    int32_t temp = 0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_handle.idx = (uint16_t)temp;
//  }
//  UniformInfo & _info = MISSING_TYPE<UniformInfo &>;
//  bgfx_get_uniform_info(arg_handle, _info);
//  return NULL;
//}

napi_value nbgfx_destroy_uniform(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_uniform_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_destroy_uniform(arg_handle);
  return NULL;
}

napi_value nbgfx_create_occlusion_query(napi_env env, napi_callback_info info){
  bgfx_occlusion_query_handle_t _ret = bgfx_create_occlusion_query();
  napi_value _napi_ret;
  {
    ASSERT_OK(napi_create_int32(env, (int32_t)_ret.idx, &_napi_ret))
  }
  return _napi_ret;
}

//napi_value nbgfx_get_result(napi_env env, napi_callback_info info){
//  napi_value argv[2];
//  GET_ARGS(2)
//  bgfx_occlusion_query_handle_t arg_handle;
//  {
//    int32_t temp = 0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_handle.idx = (uint16_t)temp;
//  }
//  int32_t* _result = MISSING_TYPE<int32_t*>;
//  bgfx_occlusion_query_result_t _ret = bgfx_get_result(arg_handle, _result);
//  napi_value _napi_ret;
//  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
//  return _napi_ret;
//}

napi_value nbgfx_destroy_occlusion_query(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_occlusion_query_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_destroy_occlusion_query(arg_handle);
  return NULL;
}

//napi_value nbgfx_set_palette_color(napi_env env, napi_callback_info info){
//  napi_value argv[2];
//  GET_ARGS(2)
//  uint8_t arg_index;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_index = (uint8_t)temp;
//  }
//  const float[4] _rgba = MISSING_TYPE<const float[4]>;
//  bgfx_set_palette_color(arg_index, _rgba);
//  return NULL;
//}

napi_value nbgfx_set_palette_color_rgba8(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  uint8_t arg_index;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_index = (uint8_t)temp;
  }
  uint32_t arg_rgba;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_rgba = (uint32_t)temp;
  }
  bgfx_set_palette_color_rgba8(arg_index, arg_rgba);
  return NULL;
}

napi_value nbgfx_set_view_name(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  char* arg_name = magic_global_string_buffer;
  size_t _temp_size_1 = 0;
  size_t _temp_size_out_1 = 0;
  {
    ASSERT_OK(napi_get_value_string_utf8(env, argv[1], arg_name, _temp_size_1 &_temp_size_out_1))
  }
  bgfx_set_view_name(arg_id, arg_name);
  return NULL;
}

napi_value nbgfx_set_view_rect(napi_env env, napi_callback_info info){
  napi_value argv[5];
  GET_ARGS(5)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  uint16_t arg_x;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_x = (uint16_t)temp;
  }
  uint16_t arg_y;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_y = (uint16_t)temp;
  }
  uint16_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_width = (uint16_t)temp;
  }
  uint16_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_height = (uint16_t)temp;
  }
  bgfx_set_view_rect(arg_id, arg_x, arg_y, arg_width, arg_height);
  return NULL;
}

napi_value nbgfx_set_view_rect_ratio(napi_env env, napi_callback_info info){
  napi_value argv[4];
  GET_ARGS(4)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  uint16_t arg_x;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_x = (uint16_t)temp;
  }
  uint16_t arg_y;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_y = (uint16_t)temp;
  }
  bgfx_backbuffer_ratio_t arg_ratio;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_ratio = (bgfx_backbuffer_ratio_t)temp;
  }
  bgfx_set_view_rect_ratio(arg_id, arg_x, arg_y, arg_ratio);
  return NULL;
}

napi_value nbgfx_set_view_scissor(napi_env env, napi_callback_info info){
  napi_value argv[5];
  GET_ARGS(5)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  uint16_t arg_x;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_x = (uint16_t)temp;
  }
  uint16_t arg_y;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_y = (uint16_t)temp;
  }
  uint16_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_width = (uint16_t)temp;
  }
  uint16_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_height = (uint16_t)temp;
  }
  bgfx_set_view_scissor(arg_id, arg_x, arg_y, arg_width, arg_height);
  return NULL;
}

napi_value nbgfx_set_view_clear(napi_env env, napi_callback_info info){
  napi_value argv[5];
  GET_ARGS(5)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  uint16_t arg_flags;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_flags = (uint16_t)temp;
  }
  uint32_t arg_rgba;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_rgba = (uint32_t)temp;
  }
  float arg_depth;
  {
    double temp = (double)0;
    ASSERT_OK(napi_get_value_double(env, argv[3], &temp))
    arg_depth = (float)temp;
  }
  uint8_t arg_stencil;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_stencil = (uint8_t)temp;
  }
  bgfx_set_view_clear(arg_id, arg_flags, arg_rgba, arg_depth, arg_stencil);
  return NULL;
}

napi_value nbgfx_set_view_clear_mrt(napi_env env, napi_callback_info info){
  napi_value argv[12];
  GET_ARGS(12)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  uint16_t arg_flags;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_flags = (uint16_t)temp;
  }
  float arg_depth;
  {
    double temp = (double)0;
    ASSERT_OK(napi_get_value_double(env, argv[2], &temp))
    arg_depth = (float)temp;
  }
  uint8_t arg_stencil;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_stencil = (uint8_t)temp;
  }
  uint8_t arg_c0;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_c0 = (uint8_t)temp;
  }
  uint8_t arg_c1;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[5], &temp))
    arg_c1 = (uint8_t)temp;
  }
  uint8_t arg_c2;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[6], &temp))
    arg_c2 = (uint8_t)temp;
  }
  uint8_t arg_c3;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[7], &temp))
    arg_c3 = (uint8_t)temp;
  }
  uint8_t arg_c4;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[8], &temp))
    arg_c4 = (uint8_t)temp;
  }
  uint8_t arg_c5;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[9], &temp))
    arg_c5 = (uint8_t)temp;
  }
  uint8_t arg_c6;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[10], &temp))
    arg_c6 = (uint8_t)temp;
  }
  uint8_t arg_c7;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[11], &temp))
    arg_c7 = (uint8_t)temp;
  }
  bgfx_set_view_clear_mrt(arg_id, arg_flags, arg_depth, arg_stencil, arg_c0, arg_c1, arg_c2, arg_c3, arg_c4, arg_c5, arg_c6, arg_c7);
  return NULL;
}

napi_value nbgfx_set_view_mode(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  bgfx_view_mode_t arg_mode;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_mode = (bgfx_view_mode_t)temp;
  }
  bgfx_set_view_mode(arg_id, arg_mode);
  return NULL;
}

napi_value nbgfx_set_view_frame_buffer(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  bgfx_frame_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_set_view_frame_buffer(arg_id, arg_handle);
  return NULL;
}

napi_value nbgfx_set_view_transform(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  uint32_t _size_1 = 0;
  void* arg_view = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[1], &arg_view, &_size_1))
  }
  uint32_t _size_2 = 0;
  void* arg_proj = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[2], &arg_proj, &_size_2))
  }
  bgfx_set_view_transform(arg_id, arg_view, arg_proj);
  return NULL;
}

//napi_value nbgfx_set_view_order(napi_env env, napi_callback_info info){
//  napi_value argv[3];
//  GET_ARGS(3)
//  bgfx_view_id_t arg_id;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_id = (bgfx_view_id_t)temp;
//  }
//  uint16_t arg_num;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_num = (uint16_t)temp;
//  }
//  const ViewId* _order = MISSING_TYPE<const ViewId*>;
//  bgfx_set_view_order(arg_id, arg_num, _order);
//  return NULL;
//}

//napi_value nbgfx_encoder_begin(napi_env env, napi_callback_info info){
//  napi_value argv[1];
//  GET_ARGS(1)
//  bool arg_forThread;
//  {
//    bool temp = (bool)0;
//    ASSERT_OK(napi_get_value_bool(env, argv[0], &temp))
//    arg_forThread = (bool)temp;
//  }
//}

//napi_value nbgfx_encoder_end(napi_env env, napi_callback_info info){
//  napi_value argv[1];
//  GET_ARGS(1)
//  Encoder* _encoder = MISSING_TYPE<Encoder*>;
//  bgfx_encoder_end(_encoder);
//  return NULL;
//}

napi_value nbgfx_request_screen_shot(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  bgfx_frame_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  char* arg_filePath = magic_global_string_buffer;
  size_t _temp_size_1 = 0;
  size_t _temp_size_out_1 = 0;
  {
    ASSERT_OK(napi_get_value_string_utf8(env, argv[1], arg_filePath, _temp_size_1 &_temp_size_out_1))
  }
  bgfx_request_screen_shot(arg_handle, arg_filePath);
  return NULL;
}

napi_value nbgfx_render_frame(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  int32_t arg_msecs;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_msecs = (int32_t)temp;
  }
  bgfx_render_frame_t _ret = bgfx_render_frame(arg_msecs);
  napi_value _napi_ret;
  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
  return _napi_ret;
}

napi_value nbgfx_set_platform_data(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_platform_data_t* arg_data = NULL;
  {
    ASSERT_OK(napi_get_value_external(env, argv[0], &arg_data))
  }
  bgfx_set_platform_data(arg_data);
  return NULL;
}

//napi_value nbgfx_get_internal_data(napi_env env, napi_callback_info info){
//}

//napi_value nbgfx_override_internal_texture_ptr(napi_env env, napi_callback_info info){
//  napi_value argv[2];
//  GET_ARGS(2)
//  bgfx_texture_handle_t arg_handle;
//  {
//    int32_t temp = 0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_handle.idx = (uint16_t)temp;
//  }
//  uintptr_t _ptr = MISSING_TYPE<uintptr_t>;
//}

//napi_value nbgfx_override_internal_texture(napi_env env, napi_callback_info info){
//  napi_value argv[6];
//  GET_ARGS(6)
//  bgfx_texture_handle_t arg_handle;
//  {
//    int32_t temp = 0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_handle.idx = (uint16_t)temp;
//  }
//  uint16_t arg_width;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_width = (uint16_t)temp;
//  }
//  uint16_t arg_height;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
//    arg_height = (uint16_t)temp;
//  }
//  uint8_t arg_numMips;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
//    arg_numMips = (uint8_t)temp;
//  }
//  bgfx_texture_format_t arg_format;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
//    arg_format = (bgfx_texture_format_t)temp;
//  }
//  uint64_t arg_flags;
//  {
//    int64_t temp = (int64_t)0;
//    ASSERT_OK(napi_get_value_int64(env, argv[5], &temp))
//    arg_flags = (uint64_t)temp;
//  }
//}

napi_value nbgfx_set_marker(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  char* arg_marker = magic_global_string_buffer;
  size_t _temp_size_0 = 0;
  size_t _temp_size_out_0 = 0;
  {
    ASSERT_OK(napi_get_value_string_utf8(env, argv[0], arg_marker, _temp_size_0 &_temp_size_out_0))
  }
  bgfx_set_marker(arg_marker);
  return NULL;
}

napi_value nbgfx_set_state(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  uint64_t arg_state;
  {
    int64_t temp = (int64_t)0;
    ASSERT_OK(napi_get_value_int64(env, argv[0], &temp))
    arg_state = (uint64_t)temp;
  }
  uint32_t arg_rgba;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_rgba = (uint32_t)temp;
  }
  bgfx_set_state(arg_state, arg_rgba);
  return NULL;
}

napi_value nbgfx_set_condition(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  bgfx_occlusion_query_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bool arg_visible;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[1], &temp))
    arg_visible = (bool)temp;
  }
  bgfx_set_condition(arg_handle, arg_visible);
  return NULL;
}

napi_value nbgfx_set_stencil(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  uint32_t arg_fstencil;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_fstencil = (uint32_t)temp;
  }
  uint32_t arg_bstencil;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_bstencil = (uint32_t)temp;
  }
  bgfx_set_stencil(arg_fstencil, arg_bstencil);
  return NULL;
}

napi_value nbgfx_set_scissor(napi_env env, napi_callback_info info){
  napi_value argv[4];
  GET_ARGS(4)
  uint16_t arg_x;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_x = (uint16_t)temp;
  }
  uint16_t arg_y;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_y = (uint16_t)temp;
  }
  uint16_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_width = (uint16_t)temp;
  }
  uint16_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_height = (uint16_t)temp;
  }
  uint16_t _ret = bgfx_set_scissor(arg_x, arg_y, arg_width, arg_height);
  napi_value _napi_ret;
  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
  return _napi_ret;
}

napi_value nbgfx_set_scissor_cached(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  uint16_t arg_cache;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_cache = (uint16_t)temp;
  }
  bgfx_set_scissor_cached(arg_cache);
  return NULL;
}

napi_value nbgfx_set_transform(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  uint32_t _size_0 = 0;
  void* arg_mtx = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[0], &arg_mtx, &_size_0))
  }
  uint16_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_num = (uint16_t)temp;
  }
  uint32_t _ret = bgfx_set_transform(arg_mtx, arg_num);
  napi_value _napi_ret;
  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
  return _napi_ret;
}

napi_value nbgfx_set_transform_cached(napi_env env, napi_callback_info info){
  napi_value argv[2];
  GET_ARGS(2)
  uint32_t arg_cache;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_cache = (uint32_t)temp;
  }
  uint16_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_num = (uint16_t)temp;
  }
  bgfx_set_transform_cached(arg_cache, arg_num);
  return NULL;
}

//napi_value nbgfx_alloc_transform(napi_env env, napi_callback_info info){
//  napi_value argv[2];
//  GET_ARGS(2)
//  Transform* _transform = MISSING_TYPE<Transform*>;
//  uint16_t arg_num;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_num = (uint16_t)temp;
//  }
//  uint32_t _ret = bgfx_alloc_transform(_transform, arg_num);
//  napi_value _napi_ret;
//  ASSERT_OK(napi_create_int32(env, (int32_t)_ret, &_napi_ret))
//  return _napi_ret;
//}

napi_value nbgfx_set_uniform(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_uniform_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint32_t _size_1 = 0;
  void* arg_value = NULL;
  {
    ASSERT_OK(napi_get_arraybuffer_info(env, argv[1], &arg_value, &_size_1))
  }
  uint16_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_num = (uint16_t)temp;
  }
  bgfx_set_uniform(arg_handle, arg_value, arg_num);
  return NULL;
}

napi_value nbgfx_set_index_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_index_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint32_t arg_firstIndex;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_firstIndex = (uint32_t)temp;
  }
  uint32_t arg_numIndices;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_numIndices = (uint32_t)temp;
  }
  bgfx_set_index_buffer(arg_handle, arg_firstIndex, arg_numIndices);
  return NULL;
}

napi_value nbgfx_set_dynamic_index_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_dynamic_index_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint32_t arg_firstIndex;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_firstIndex = (uint32_t)temp;
  }
  uint32_t arg_numIndices;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_numIndices = (uint32_t)temp;
  }
  bgfx_set_dynamic_index_buffer(arg_handle, arg_firstIndex, arg_numIndices);
  return NULL;
}

//napi_value nbgfx_set_transient_index_buffer(napi_env env, napi_callback_info info){
//  napi_value argv[3];
//  GET_ARGS(3)
//  const TransientIndexBuffer* _tib = MISSING_TYPE<const TransientIndexBuffer*>;
//  uint32_t arg_firstIndex;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_firstIndex = (uint32_t)temp;
//  }
//  uint32_t arg_numIndices;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
//    arg_numIndices = (uint32_t)temp;
//  }
//  bgfx_set_transient_index_buffer(_tib, arg_firstIndex, arg_numIndices);
//  return NULL;
//}

napi_value nbgfx_set_vertex_buffer(napi_env env, napi_callback_info info){
  napi_value argv[4];
  GET_ARGS(4)
  uint8_t arg_stream;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_stream = (uint8_t)temp;
  }
  bgfx_vertex_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint32_t arg_startVertex;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_startVertex = (uint32_t)temp;
  }
  uint32_t arg_numVertices;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_numVertices = (uint32_t)temp;
  }
  bgfx_set_vertex_buffer(arg_stream, arg_handle, arg_startVertex, arg_numVertices);
  return NULL;
}

napi_value nbgfx_set_dynamic_vertex_buffer(napi_env env, napi_callback_info info){
  napi_value argv[4];
  GET_ARGS(4)
  uint8_t arg_stream;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_stream = (uint8_t)temp;
  }
  bgfx_dynamic_vertex_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint32_t arg_startVertex;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_startVertex = (uint32_t)temp;
  }
  uint32_t arg_numVertices;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_numVertices = (uint32_t)temp;
  }
  bgfx_set_dynamic_vertex_buffer(arg_stream, arg_handle, arg_startVertex, arg_numVertices);
  return NULL;
}

//napi_value nbgfx_set_transient_vertex_buffer(napi_env env, napi_callback_info info){
//  napi_value argv[4];
//  GET_ARGS(4)
//  uint8_t arg_stream;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
//    arg_stream = (uint8_t)temp;
//  }
//  const TransientVertexBuffer* _tvb = MISSING_TYPE<const TransientVertexBuffer*>;
//  uint32_t arg_startVertex;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
//    arg_startVertex = (uint32_t)temp;
//  }
//  uint32_t arg_numVertices;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
//    arg_numVertices = (uint32_t)temp;
//  }
//  bgfx_set_transient_vertex_buffer(arg_stream, _tvb, arg_startVertex, arg_numVertices);
//  return NULL;
//}

napi_value nbgfx_set_vertex_count(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  uint32_t arg_numVertices;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_numVertices = (uint32_t)temp;
  }
  bgfx_set_vertex_count(arg_numVertices);
  return NULL;
}

//napi_value nbgfx_set_instance_data_buffer(napi_env env, napi_callback_info info){
//  napi_value argv[3];
//  GET_ARGS(3)
//  const InstanceDataBuffer* _idb = MISSING_TYPE<const InstanceDataBuffer*>;
//  uint32_t arg_start;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
//    arg_start = (uint32_t)temp;
//  }
//  uint32_t arg_num;
//  {
//    int32_t temp = (int32_t)0;
//    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
//    arg_num = (uint32_t)temp;
//  }
//  bgfx_set_instance_data_buffer(_idb, arg_start, arg_num);
//  return NULL;
//}

napi_value nbgfx_set_instance_data_from_vertex_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_vertex_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint32_t arg_startVertex;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_startVertex = (uint32_t)temp;
  }
  uint32_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_num = (uint32_t)temp;
  }
  bgfx_set_instance_data_from_vertex_buffer(arg_handle, arg_startVertex, arg_num);
  return NULL;
}

napi_value nbgfx_set_instance_data_from_dynamic_vertex_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  bgfx_dynamic_vertex_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint32_t arg_startVertex;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_startVertex = (uint32_t)temp;
  }
  uint32_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_num = (uint32_t)temp;
  }
  bgfx_set_instance_data_from_dynamic_vertex_buffer(arg_handle, arg_startVertex, arg_num);
  return NULL;
}

napi_value nbgfx_set_instance_count(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  uint32_t arg_numInstances;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_numInstances = (uint32_t)temp;
  }
  bgfx_set_instance_count(arg_numInstances);
  return NULL;
}

napi_value nbgfx_set_texture(napi_env env, napi_callback_info info){
  napi_value argv[4];
  GET_ARGS(4)
  uint8_t arg_stage;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_stage = (uint8_t)temp;
  }
  bgfx_uniform_handle_t arg_sampler;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_sampler.idx = (uint16_t)temp;
  }
  bgfx_texture_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint32_t arg_flags;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_flags = (uint32_t)temp;
  }
  bgfx_set_texture(arg_stage, arg_sampler, arg_handle, arg_flags);
  return NULL;
}

napi_value nbgfx_touch(napi_env env, napi_callback_info info){
  napi_value argv[1];
  GET_ARGS(1)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  bgfx_touch(arg_id);
  return NULL;
}

napi_value nbgfx_submit(napi_env env, napi_callback_info info){
  napi_value argv[4];
  GET_ARGS(4)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  bgfx_program_handle_t arg_program;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_program.idx = (uint16_t)temp;
  }
  uint32_t arg_depth;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_depth = (uint32_t)temp;
  }
  bool arg_preserveState;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[3], &temp))
    arg_preserveState = (bool)temp;
  }
  bgfx_submit(arg_id, arg_program, arg_depth, arg_preserveState);
  return NULL;
}

napi_value nbgfx_submit_occlusion_query(napi_env env, napi_callback_info info){
  napi_value argv[5];
  GET_ARGS(5)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  bgfx_program_handle_t arg_program;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_program.idx = (uint16_t)temp;
  }
  bgfx_occlusion_query_handle_t arg_occlusionQuery;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_occlusionQuery.idx = (uint16_t)temp;
  }
  uint32_t arg_depth;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_depth = (uint32_t)temp;
  }
  bool arg_preserveState;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[4], &temp))
    arg_preserveState = (bool)temp;
  }
  bgfx_submit_occlusion_query(arg_id, arg_program, arg_occlusionQuery, arg_depth, arg_preserveState);
  return NULL;
}

napi_value nbgfx_submit_indirect(napi_env env, napi_callback_info info){
  napi_value argv[7];
  GET_ARGS(7)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  bgfx_program_handle_t arg_program;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_program.idx = (uint16_t)temp;
  }
  bgfx_indirect_buffer_handle_t arg_indirectHandle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_indirectHandle.idx = (uint16_t)temp;
  }
  uint16_t arg_start;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_start = (uint16_t)temp;
  }
  uint16_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_num = (uint16_t)temp;
  }
  uint32_t arg_depth;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[5], &temp))
    arg_depth = (uint32_t)temp;
  }
  bool arg_preserveState;
  {
    bool temp = (bool)0;
    ASSERT_OK(napi_get_value_bool(env, argv[6], &temp))
    arg_preserveState = (bool)temp;
  }
  bgfx_submit_indirect(arg_id, arg_program, arg_indirectHandle, arg_start, arg_num, arg_depth, arg_preserveState);
  return NULL;
}

napi_value nbgfx_set_compute_index_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  uint8_t arg_stage;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_stage = (uint8_t)temp;
  }
  bgfx_index_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_access_t arg_access;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_access = (bgfx_access_t)temp;
  }
  bgfx_set_compute_index_buffer(arg_stage, arg_handle, arg_access);
  return NULL;
}

napi_value nbgfx_set_compute_vertex_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  uint8_t arg_stage;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_stage = (uint8_t)temp;
  }
  bgfx_vertex_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_access_t arg_access;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_access = (bgfx_access_t)temp;
  }
  bgfx_set_compute_vertex_buffer(arg_stage, arg_handle, arg_access);
  return NULL;
}

napi_value nbgfx_set_compute_dynamic_index_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  uint8_t arg_stage;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_stage = (uint8_t)temp;
  }
  bgfx_dynamic_index_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_access_t arg_access;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_access = (bgfx_access_t)temp;
  }
  bgfx_set_compute_dynamic_index_buffer(arg_stage, arg_handle, arg_access);
  return NULL;
}

napi_value nbgfx_set_compute_dynamic_vertex_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  uint8_t arg_stage;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_stage = (uint8_t)temp;
  }
  bgfx_dynamic_vertex_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_access_t arg_access;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_access = (bgfx_access_t)temp;
  }
  bgfx_set_compute_dynamic_vertex_buffer(arg_stage, arg_handle, arg_access);
  return NULL;
}

napi_value nbgfx_set_compute_indirect_buffer(napi_env env, napi_callback_info info){
  napi_value argv[3];
  GET_ARGS(3)
  uint8_t arg_stage;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_stage = (uint8_t)temp;
  }
  bgfx_indirect_buffer_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  bgfx_access_t arg_access;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_access = (bgfx_access_t)temp;
  }
  bgfx_set_compute_indirect_buffer(arg_stage, arg_handle, arg_access);
  return NULL;
}

napi_value nbgfx_set_image(napi_env env, napi_callback_info info){
  napi_value argv[5];
  GET_ARGS(5)
  uint8_t arg_stage;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_stage = (uint8_t)temp;
  }
  bgfx_texture_handle_t arg_handle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_handle.idx = (uint16_t)temp;
  }
  uint8_t arg_mip;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_mip = (uint8_t)temp;
  }
  bgfx_access_t arg_access;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_access = (bgfx_access_t)temp;
  }
  bgfx_texture_format_t arg_format;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_format = (bgfx_texture_format_t)temp;
  }
  bgfx_set_image(arg_stage, arg_handle, arg_mip, arg_access, arg_format);
  return NULL;
}

napi_value nbgfx_dispatch(napi_env env, napi_callback_info info){
  napi_value argv[5];
  GET_ARGS(5)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  bgfx_program_handle_t arg_program;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_program.idx = (uint16_t)temp;
  }
  uint32_t arg_numX;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_numX = (uint32_t)temp;
  }
  uint32_t arg_numY;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_numY = (uint32_t)temp;
  }
  uint32_t arg_numZ;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_numZ = (uint32_t)temp;
  }
  bgfx_dispatch(arg_id, arg_program, arg_numX, arg_numY, arg_numZ);
  return NULL;
}

napi_value nbgfx_dispatch_indirect(napi_env env, napi_callback_info info){
  napi_value argv[5];
  GET_ARGS(5)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  bgfx_program_handle_t arg_program;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_program.idx = (uint16_t)temp;
  }
  bgfx_indirect_buffer_handle_t arg_indirectHandle;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_indirectHandle.idx = (uint16_t)temp;
  }
  uint16_t arg_start;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_start = (uint16_t)temp;
  }
  uint16_t arg_num;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_num = (uint16_t)temp;
  }
  bgfx_dispatch_indirect(arg_id, arg_program, arg_indirectHandle, arg_start, arg_num);
  return NULL;
}

napi_value nbgfx_discard(napi_env env, napi_callback_info info){
  bgfx_discard();
  return NULL;
}

napi_value nbgfx_blit(napi_env env, napi_callback_info info){
  napi_value argv[14];
  GET_ARGS(14)
  bgfx_view_id_t arg_id;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[0], &temp))
    arg_id = (bgfx_view_id_t)temp;
  }
  bgfx_texture_handle_t arg_dst;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[1], &temp))
    arg_dst.idx = (uint16_t)temp;
  }
  uint8_t arg_dstMip;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[2], &temp))
    arg_dstMip = (uint8_t)temp;
  }
  uint16_t arg_dstX;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[3], &temp))
    arg_dstX = (uint16_t)temp;
  }
  uint16_t arg_dstY;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[4], &temp))
    arg_dstY = (uint16_t)temp;
  }
  uint16_t arg_dstZ;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[5], &temp))
    arg_dstZ = (uint16_t)temp;
  }
  bgfx_texture_handle_t arg_src;
  {
    int32_t temp = 0;
    ASSERT_OK(napi_get_value_int32(env, argv[6], &temp))
    arg_src.idx = (uint16_t)temp;
  }
  uint8_t arg_srcMip;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[7], &temp))
    arg_srcMip = (uint8_t)temp;
  }
  uint16_t arg_srcX;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[8], &temp))
    arg_srcX = (uint16_t)temp;
  }
  uint16_t arg_srcY;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[9], &temp))
    arg_srcY = (uint16_t)temp;
  }
  uint16_t arg_srcZ;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[10], &temp))
    arg_srcZ = (uint16_t)temp;
  }
  uint16_t arg_width;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[11], &temp))
    arg_width = (uint16_t)temp;
  }
  uint16_t arg_height;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[12], &temp))
    arg_height = (uint16_t)temp;
  }
  uint16_t arg_depth;
  {
    int32_t temp = (int32_t)0;
    ASSERT_OK(napi_get_value_int32(env, argv[13], &temp))
    arg_depth = (uint16_t)temp;
  }
  bgfx_blit(arg_id, arg_dst, arg_dstMip, arg_dstX, arg_dstY, arg_dstZ, arg_src, arg_srcMip, arg_srcX, arg_srcY, arg_srcZ, arg_width, arg_height, arg_depth);
  return NULL;
}

