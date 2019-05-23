#include "bgfx_draw.hpp"
#include "bgfx_converters.hpp"

constexpr uintptr_t IS_DYNAMIC_MASK = (1<<31);

constexpr bool is_dynamic_handle(uintptr_t handle) {
  return (handle & IS_DYNAMIC_MASK);
}

template<typename T>
constexpr T to_handle(uintptr_t handle) {
  T result;
  result.idx = handle;
  return result;
}

void bgfx_draw(bgfx_drawcall_t drawcall)
{
  bgfx_set_transform(drawcall.xform, 1);

  if (is_dynamic_handle(drawcall.index.buffer))
  {
    bgfx_set_dynamic_index_buffer(
        to_handle<bgfx_dynamic_index_buffer_handle_t>(drawcall.index.buffer),
        drawcall.index.first,
        drawcall.index.numIndices);
  }
  else
  {
    bgfx_set_index_buffer(
        to_handle<bgfx_index_buffer_handle_t>(drawcall.index.buffer),
        drawcall.index.first,
        drawcall.index.numIndices);
  }

  if (is_dynamic_handle(drawcall.vertex.buffer))
  {
    bgfx_set_dynamic_vertex_buffer(
        drawcall.vertex.stream,
        to_handle<bgfx_dynamic_vertex_buffer_handle_t>(drawcall.vertex.buffer),
        drawcall.vertex.first,
        drawcall.vertex.numIndices);
  }
  else
  {
    bgfx_set_vertex_buffer(
        drawcall.vertex.stream,
        to_handle<bgfx_vertex_buffer_handle_t>(drawcall.vertex.buffer),
        drawcall.vertex.first,
        drawcall.vertex.numIndices);
  }

  for (const auto uniform : drawcall.uniforms)
  {
    // FIXME: allow specification of `num`.
    bgfx_set_uniform(uniform.handle, uniform.value, uniform.num);
  }

  bgfx_set_state(drawcall.state, drawcall.rgba);
  bgfx_submit(drawcall.view, drawcall.program, drawcall.depth, drawcall.preserve_state);
}

namespace wrap
{

template <>
bgfx_drawcall_t decode(napi_env env, napi_value value)
{
  bgfx_drawcall_t result;

  result.xform = wrap::decode_property<bgfx_mat4_t *>(env, value, "xform");
  result.state = wrap::decode_property<uint64_t>(env, value, "state");
  result.rgba = wrap::decode_property<uint32_t>(env, value, "rgba");
  result.depth = wrap::decode_property<uint32_t>(env, value, "rgba");
  result.index;
  result.vertex;
  result.uniforms;

  return result;
}

} // namespace wrap