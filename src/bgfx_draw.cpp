#include "bgfx_draw.hpp"

void bgfx_draw(bgfx_drawcall_t drawcall)
{
  bgfx_set_transform(drawcall.xform, 1);

  if (is_dynamic_handle(drawcall.index.buffer))
  {
    bgfx_set_dynamic_index_buffer(
        to_index_handle(drawcall.index_buffer),
        drawcall.index.first,
        drawcall.index.numIndices);
  }
  else
  {
    bgfx_set_index_buffer(
        to_index_handle(drawcall.index.buffer),
        drawcall.index.first,
        drawcall.index.numIndices);
  }

  if (is_dynamic_handle(drawcall.vertex.buffer))
  {
    bgfx_set_dynamic_vertex_buffer(
        drawcall.vertex.stream,
        drawcall.vertex.buffer,
        drawcall.vertex.first,
        drawcall.vertex.numIndices);
  }
  else
  {
    bgfx_set_vertex_buffer(
        drawcall.vertex.stream,
        drawcall.vertex.buffer,
        drawcall.vertex.first,
        drawcall.vertex.numIndices);
  }

  for (const auto uniform : uniforms)
  {
    bgfx_set_uniform(handle, value, cnt);
  }

  bgfx_set_state(drawcall.state, drawcall.rgba);
  bgfx_submit(drawcall.view, drawcall.program, drawcall.depth, drawcall.preserveState);
}