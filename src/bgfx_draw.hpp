#pragma once
#include "bgfx_converters.hpp"
#include <bgfx/c99/bgfx.h>
#include <node_api.h>
#include <tuple>
#include <vector>

using bgfx_uniform_vec_t = std::vector<std::tuple<bgfx_uniform_handle_t, void *>>;

struct bgfx_index_buffer_args_t
{
  void *handle;
  uint32_t first;
  uint32_t numIndices;
};

struct bgfx_vertex_buffer_args_t
{
  uint8_t stream;
  void *handle;
  uint32_t first;
  uint32_t numIndices;
};

struct bgfx_drawcall_t
{
  bgfx_mat4_t *xform;
  uint64_t state;
  uint32_t rgba;
  bgfx_index_buffer_args_t index;
  bgfx_vertex_buffer_args_t vertex;
  bgfx_uniform_vec_t uniforms;
};

void bgfx_draw(bgfx_drawcall_t drawcall);

namespace wrap
{
//===========================================================================
template <>
inline bgfx_drawcall_t decode(napi_env env, napi_value value)
{
  bgfx_drawcall_t result;
  return result;
}

} // namespace wrap