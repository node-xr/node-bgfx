#include "bgfx_converters.hpp"
#include "bgfx_draw.hpp"
#include <iostream>
#include <napi_bind.hpp>

using napi_bind::ok;

const std::vector<bgfx_uniform_args_t> EMPTY_UNIFORMS;
const std::vector<bgfx_texture_args_t> EMPTY_TEXTURES;
const bgfx_mat4_t IDENTITY_MATRIX = {{1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1}};

void bgfx_draw(bgfx_drawcall_t drawcall)
{
  bgfx_set_transform(drawcall.xform, 1);

  if (drawcall.index)
  {
    auto index = *drawcall.index;
    if (bgfx_get_handle_type(index.buffer) == bgfx_handle_type::dynamic_index_buffer)
    {
      bgfx_set_dynamic_index_buffer(
          bgfx_unpack_handle<bgfx_dynamic_index_buffer_handle_t>(index.buffer),
          index.first,
          index.numIndices);
    }
    else if (bgfx_get_handle_type(index.buffer) == bgfx_handle_type::index_buffer)
    {
      bgfx_set_index_buffer(
          bgfx_unpack_handle<bgfx_index_buffer_handle_t>(index.buffer),
          index.first,
          index.numIndices);
    }
    else
    {
      throw std::runtime_error("Invalid index buffer handle.");
    }
  }

  if (drawcall.vertex)
  {
    auto vertex = *drawcall.vertex;
    if (bgfx_get_handle_type(vertex.buffer) == bgfx_handle_type::dynamic_vertex_buffer)
    {
      bgfx_set_dynamic_vertex_buffer(
          vertex.stream,
          bgfx_unpack_handle<bgfx_dynamic_vertex_buffer_handle_t>(vertex.buffer),
          vertex.first,
          vertex.numIndices);
    }
    else if (bgfx_get_handle_type(vertex.buffer) == bgfx_handle_type::vertex_buffer)
    {
      bgfx_set_vertex_buffer(
          vertex.stream,
          bgfx_unpack_handle<bgfx_vertex_buffer_handle_t>(vertex.buffer),
          vertex.first,
          vertex.numIndices);
    }
    else
    {
      throw std::runtime_error("Invalid vertex buffer handle.");
    }
  }

  for (const auto args : drawcall.uniforms)
  {
    bgfx_set_uniform(args.handle, args.value, args.num);
  }

  for (const auto args : drawcall.textures)
  {
    bgfx_set_texture(args.stage, args.handle, args.texture, args.flags);
  }

  bgfx_set_state(drawcall.state, drawcall.rgba);
  bgfx_submit(drawcall.view, drawcall.program, drawcall.depth, drawcall.preserve_state);
}
