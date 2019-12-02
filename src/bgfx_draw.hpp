#pragma once
#include "bgfx_converters.hpp"
#include <bgfx/c99/bgfx.h>
#include <optional>
#include <tuple>
#include <vector>

struct bgfx_index_buffer_args_t
{
  uint32_t buffer;
  uint32_t first;
  uint32_t numIndices;
};

struct bgfx_vertex_buffer_args_t
{
  uint8_t stream;
  uint32_t buffer;
  uint32_t first;
  uint32_t numIndices;
};

struct bgfx_uniform_args_t
{
  bgfx_uniform_handle_t handle;
  void *value;
  uint32_t num;
};

struct bgfx_texture_args_t
{
  bgfx_uniform_handle_t handle;
  uint8_t stage;
  bgfx_texture_handle_t texture;
  uint32_t flags;
};

struct bgfx_drawcall_t
{
  bgfx_mat4_t *xform;
  uint64_t state;
  uint32_t rgba;
  uint32_t depth;
  std::optional<bgfx_index_buffer_args_t> index;
  std::optional<bgfx_vertex_buffer_args_t> vertex;
  std::vector<bgfx_uniform_args_t> uniforms;
  std::vector<bgfx_texture_args_t> textures;
  bgfx_view_id_t view;
  bgfx_program_handle_t program;
  bool preserve_state;
};

void bgfx_draw(bgfx_drawcall_t drawcall);

extern const std::vector<bgfx_uniform_args_t> EMPTY_UNIFORMS;
extern const std::vector<bgfx_texture_args_t> EMPTY_TEXTURES;
extern const bgfx_mat4_t IDENTITY_MATRIX;

#include "bgfx_draw_impl.hpp"