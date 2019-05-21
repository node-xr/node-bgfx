#pragma once
#include <node_api.h>
#include "bgfx.hpp"

namespace wrap
{

//===========================================================================
template <>
inline const bgfx_memory_t *decode(napi_env env, napi_value value)
{
  void *ptr;
  size_t len;
  ok(napi_get_arraybuffer_info(env, value, &ptr, &len));
  return bgfx_copy(ptr, len);
}

//===========================================================================
void bgfx_finalize_index_buffer(napi_env env, void *data, void *hint)
{
  auto handle = reinterpret_cast<uintptr_t>(data);

  bgfx_index_buffer_handle_t result;
  result.idx = handle;
  bgfx_destroy_index_buffer(result);
}

template <>
inline bgfx_index_buffer_handle_t decode(napi_env env, napi_value value)
{
  uintptr_t handle;
  ok(napi_get_value_external(env, value, reinterpret_cast<void **>(&handle)));

  bgfx_index_buffer_handle_t result;
  result.idx = handle;
  return result;
}

template <>
inline napi_value encode(napi_env env, bgfx_index_buffer_handle_t value)
{
  napi_value result;
  ok(napi_create_external(env, reinterpret_cast<void *>(value.idx), bgfx_finalize_index_buffer, nullptr, &result));
  return result;
}

//===========================================================================
void bgfx_finalize_dynamic_index_buffer(napi_env env, void *data, void *hint)
{
  auto handle = reinterpret_cast<uintptr_t>(data);

  bgfx_dynamic_index_buffer_handle_t result;
  result.idx = handle;
  bgfx_destroy_dynamic_index_buffer(result);
}

template <>
inline bgfx_dynamic_index_buffer_handle_t decode(napi_env env, napi_value value)
{
  uintptr_t handle;
  ok(napi_get_value_external(env, value, reinterpret_cast<void **>(&handle)));

  bgfx_dynamic_index_buffer_handle_t result;
  result.idx = handle;
  return result;
}

template <>
inline napi_value encode(napi_env env, bgfx_dynamic_index_buffer_handle_t value)
{
  napi_value result;
  ok(napi_create_external(env, reinterpret_cast<void *>(value.idx), bgfx_finalize_dynamic_index_buffer, nullptr, &result));
  return result;
}

//===========================================================================
void bgfx_finalize_vertex_buffer(napi_env env, void *data, void *hint)
{
  auto handle = reinterpret_cast<uintptr_t>(data);

  bgfx_vertex_buffer_handle_t result;
  result.idx = handle;
  bgfx_destroy_vertex_buffer(result);
}

template <>
inline bgfx_vertex_buffer_handle_t decode(napi_env env, napi_value value)
{
  uintptr_t handle;
  ok(napi_get_value_external(env, value, reinterpret_cast<void **>(&handle)));

  bgfx_vertex_buffer_handle_t result;
  result.idx = handle;
  return result;
}

template <>
inline napi_value encode(napi_env env, bgfx_vertex_buffer_handle_t value)
{
  napi_value result;
  ok(napi_create_external(env, reinterpret_cast<void *>(value.idx), bgfx_finalize_vertex_buffer, nullptr, &result));
  return result;
}

//===========================================================================
void bgfx_finalize_dynamic_vertex_buffer(napi_env env, void *data, void *hint)
{
  auto handle = reinterpret_cast<uintptr_t>(data);

  bgfx_dynamic_vertex_buffer_handle_t result;
  result.idx = handle;
  bgfx_destroy_dynamic_vertex_buffer(result);
}

template <>
inline bgfx_dynamic_vertex_buffer_handle_t decode(napi_env env, napi_value value)
{
  uintptr_t handle;
  ok(napi_get_value_external(env, value, reinterpret_cast<void **>(&handle)));

  bgfx_dynamic_vertex_buffer_handle_t result;
  result.idx = handle;
  return result;
}

template <>
inline napi_value encode(napi_env env, bgfx_dynamic_vertex_buffer_handle_t value)
{
  napi_value result;
  ok(napi_create_external(env, reinterpret_cast<void *>(value.idx), bgfx_finalize_dynamic_vertex_buffer, nullptr, &result));
  return result;
}

//===========================================================================
void bgfx_finalize_indirect_buffer(napi_env env, void *data, void *hint)
{
  auto handle = reinterpret_cast<uintptr_t>(data);

  bgfx_indirect_buffer_handle_t result;
  result.idx = handle;
  bgfx_destroy_indirect_buffer(result);
}

template <>
inline bgfx_indirect_buffer_handle_t decode(napi_env env, napi_value value)
{
  uintptr_t handle;
  ok(napi_get_value_external(env, value, reinterpret_cast<void **>(&handle)));

  bgfx_indirect_buffer_handle_t result;
  result.idx = handle;
  return result;
}

template <>
inline napi_value encode(napi_env env, bgfx_indirect_buffer_handle_t value)
{
  napi_value result;
  ok(napi_create_external(env, reinterpret_cast<void *>(value.idx), bgfx_finalize_indirect_buffer, nullptr, &result));
  return result;
}

//===========================================================================
void bgfx_finalize_shader(napi_env env, void *data, void *hint)
{
  auto handle = reinterpret_cast<uintptr_t>(data);

  bgfx_shader_handle_t result;
  result.idx = handle;
  bgfx_destroy_shader(result);
}

template <>
inline bgfx_shader_handle_t decode(napi_env env, napi_value value)
{
  uintptr_t handle;
  ok(napi_get_value_external(env, value, reinterpret_cast<void **>(&handle)));

  bgfx_shader_handle_t result;
  result.idx = handle;
  return result;
}

template <>
inline napi_value encode(napi_env env, bgfx_shader_handle_t value)
{
  napi_value result;
  ok(napi_create_external(env, reinterpret_cast<void *>(value.idx), bgfx_finalize_shader, nullptr, &result));
  return result;
}

//===========================================================================
void bgfx_finalize_program(napi_env env, void *data, void *hint)
{
  auto handle = reinterpret_cast<uintptr_t>(data);

  bgfx_program_handle_t result;
  result.idx = handle;
  bgfx_destroy_program(result);
}

template <>
inline bgfx_program_handle_t decode(napi_env env, napi_value value)
{
  uintptr_t handle;
  ok(napi_get_value_external(env, value, reinterpret_cast<void **>(&handle)));

  bgfx_program_handle_t result;
  result.idx = handle;
  return result;
}

template <>
inline napi_value encode(napi_env env, bgfx_program_handle_t value)
{
  napi_value result;
  ok(napi_create_external(env, reinterpret_cast<void *>(value.idx), bgfx_finalize_program, nullptr, &result));
  return result;
}

//===========================================================================
void bgfx_finalize_texture(napi_env env, void *data, void *hint)
{
  auto handle = reinterpret_cast<uintptr_t>(data);

  bgfx_texture_handle_t result;
  result.idx = handle;
  bgfx_destroy_texture(result);
}

template <>
inline bgfx_texture_handle_t decode(napi_env env, napi_value value)
{
  uintptr_t handle;
  ok(napi_get_value_external(env, value, reinterpret_cast<void **>(&handle)));

  bgfx_texture_handle_t result;
  result.idx = handle;
  return result;
}

template <>
inline napi_value encode(napi_env env, bgfx_texture_handle_t value)
{
  napi_value result;
  ok(napi_create_external(env, reinterpret_cast<void *>(value.idx), bgfx_finalize_texture, nullptr, &result));
  return result;
}

//===========================================================================
void bgfx_finalize_frame_buffer(napi_env env, void *data, void *hint)
{
  auto handle = reinterpret_cast<uintptr_t>(data);

  bgfx_frame_buffer_handle_t result;
  result.idx = handle;
  bgfx_destroy_frame_buffer(result);
}

template <>
inline bgfx_frame_buffer_handle_t decode(napi_env env, napi_value value)
{
  uintptr_t handle;
  ok(napi_get_value_external(env, value, reinterpret_cast<void **>(&handle)));

  bgfx_frame_buffer_handle_t result;
  result.idx = handle;
  return result;
}

template <>
inline napi_value encode(napi_env env, bgfx_frame_buffer_handle_t value)
{
  napi_value result;
  ok(napi_create_external(env, reinterpret_cast<void *>(value.idx), bgfx_finalize_frame_buffer, nullptr, &result));
  return result;
}

//===========================================================================
void bgfx_finalize_uniform(napi_env env, void *data, void *hint)
{
  auto handle = reinterpret_cast<uintptr_t>(data);

  bgfx_uniform_handle_t result;
  result.idx = handle;
  bgfx_destroy_uniform(result);
}

template <>
inline bgfx_uniform_handle_t decode(napi_env env, napi_value value)
{
  uintptr_t handle;
  ok(napi_get_value_external(env, value, reinterpret_cast<void **>(&handle)));

  bgfx_uniform_handle_t result;
  result.idx = handle;
  return result;
}

template <>
inline napi_value encode(napi_env env, bgfx_uniform_handle_t value)
{
  napi_value result;
  ok(napi_create_external(env, reinterpret_cast<void *>(value.idx), bgfx_finalize_uniform, nullptr, &result));
  return result;
}

//===========================================================================
void bgfx_finalize_occlusion_query(napi_env env, void *data, void *hint)
{
  auto handle = reinterpret_cast<uintptr_t>(data);

  bgfx_occlusion_query_handle_t result;
  result.idx = handle;
  bgfx_destroy_occlusion_query(result);
}

template <>
inline bgfx_occlusion_query_handle_t decode(napi_env env, napi_value value)
{
  uintptr_t handle;
  ok(napi_get_value_external(env, value, reinterpret_cast<void **>(&handle)));

  bgfx_occlusion_query_handle_t result;
  result.idx = handle;
  return result;
}

template <>
inline napi_value encode(napi_env env, bgfx_occlusion_query_handle_t value)
{
  napi_value result;
  ok(napi_create_external(env, reinterpret_cast<void *>(value.idx), bgfx_finalize_occlusion_query, nullptr, &result));
  return result;
}

//===========================================================================
struct bgfx_mat4_t
{
  float data[16];
};

template <>
inline bgfx_mat4_t *decode(napi_env env, napi_value value)
{
  size_t n;
  bgfx_mat4_t *result;
  ok(napi_get_arraybuffer_info(env, value, reinterpret_cast<void **>(&result), &n));
  if (n != sizeof(bgfx_mat4_t))
    throw std::runtime_error("Matrix 4x4 must have 16 float elements.");
  return result;
}

//===========================================================================
struct bgfx_mat4_array_t
{
  bgfx_mat4_t *head;
  size_t count;
};

template <>
inline bgfx_mat4_array_t decode(napi_env env, napi_value value)
{
  size_t n;
  bgfx_mat4_t *ptr;
  ok(napi_get_arraybuffer_info(env, value, reinterpret_cast<void **>(&ptr), &n));
  if (n % sizeof(bgfx_mat4_t))
    throw std::runtime_error("Matrix 4x4 array must have multiple of 16 float elements.");

  bgfx_mat4_array_t result;
  result.head = ptr;
  result.count = n / sizeof(bgfx_mat4_t);
  return result;
}

//===========================================================================
struct bgfx_drawcall_t
{
  uint32_t state;
  void *index_buffer;
  void *vertex_buffer;
  bgfx_mat4_array_t transform;
  std::vector<void *> uniforms;
};

template <>
inline bgfx_drawcall_t decode(napi_env env, napi_value value)
{
  bgfx_drawcall_t result;
  return result;
}

} // namespace wrap
