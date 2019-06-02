#pragma once
#include "bgfx_converters.hpp"
#include <bgfx/c99/bgfx.h>
#include <node_api.h>
#include <tuple>
#include <vector>

struct bgfx_index_buffer_args_t
{
  uintptr_t buffer;
  uint32_t first;
  uint32_t numIndices;
};

struct bgfx_vertex_buffer_args_t
{
  uint8_t stream;
  uintptr_t buffer;
  uint32_t first;
  uint32_t numIndices;
};

struct bgfx_uniform_args_t
{
  bgfx_uniform_handle_t handle;
  void *value;
  uint32_t num;
};

struct bgfx_drawcall_t
{
  bgfx_mat4_t *xform;
  uint64_t state;
  uint32_t rgba;
  uint32_t depth;
  wrap::optional<bgfx_index_buffer_args_t> index;
  wrap::optional<bgfx_vertex_buffer_args_t> vertex;
  std::vector<bgfx_uniform_args_t> uniforms;
  bgfx_view_id_t view;
  bgfx_program_handle_t program;
  bool preserve_state;
};

void bgfx_draw(bgfx_drawcall_t drawcall);

namespace wrap
{

template <>
bgfx_drawcall_t decode(napi_env env, napi_value value);

} // namespace wrap