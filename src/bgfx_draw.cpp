#include "bgfx_draw.hpp"
#include "bgfx_converters.hpp"

template <typename T>
constexpr T to_handle(uintptr_t handle)
{
  T result{};
  result.idx = handle;
  return result;
}

namespace wrap
{

template <>
inline bgfx_index_buffer_args_t decode(napi_env env, napi_value value)
{
  bgfx_index_buffer_args_t result;
  result.buffer = decode_property<uintptr_t>(env, value, "buffer");
  result.first = decode_property<uint32_t>(env, value, "first");
  result.numIndices = decode_property<uint32_t>(env, value, "numIndices");
  return result;
}

template <>
inline bgfx_vertex_buffer_args_t decode(napi_env env, napi_value value)
{
  bgfx_vertex_buffer_args_t result;
  result.buffer = decode_property<uintptr_t>(env, value, "buffer");
  result.first = decode_property<uint32_t>(env, value, "first");
  result.numIndices = decode_property<uint32_t>(env, value, "numIndices");
  return result;
}

template <>
inline bgfx_uniform_args_t decode(napi_env env, napi_value value)
{
  bgfx_uniform_args_t result;
  result.handle = decode_property<bgfx_uniform_handle_t>(env, value, "handle");
  result.value = decode_property<void *>(env, value, "value");
  result.num = decode_property<uint32_t>(env, value, "num", UINT16_MAX);
  return result;
}

template <>
bgfx_drawcall_t decode(napi_env env, napi_value value)
{
  bgfx_drawcall_t result;
  result.xform = wrap::decode_property<bgfx_mat4_t *>(env, value, "xform");
  result.state = wrap::decode_property<uint64_t>(env, value, "state");
  result.rgba = wrap::decode_property<uint32_t>(env, value, "rgba");
  result.depth = wrap::decode_property<uint32_t>(env, value, "depth");
  result.index = wrap::decode_property<bgfx_index_buffer_args_t>(env, value, "index");
  result.vertex = wrap::decode_property<bgfx_vertex_buffer_args_t>(env, value, "vertex");
  result.uniforms = wrap::decode_property<std::vector<bgfx_uniform_args_t>>(env, value, "uniforms");
  result.view = wrap::decode_property<bgfx_view_id_t>(env, value, "view");
  result.program = wrap::decode_property<bgfx_program_handle_t>(env, value, "program");
  result.preserve_state = wrap::decode_property<bool>(env, value, "preserve_state");
  return result;
}

} // namespace wrap

void bgfx_draw(bgfx_drawcall_t drawcall)
{
  bgfx_set_transform(drawcall.xform, 1);

  if (bgfx_get_handle_type(drawcall.index.buffer) == bgfx_handle_type::dynamic_index)
  {
    bgfx_set_dynamic_index_buffer(
        to_handle<bgfx_dynamic_index_buffer_handle_t>(drawcall.index.buffer),
        drawcall.index.first,
        drawcall.index.numIndices);
  }
  else if (bgfx_get_handle_type(drawcall.index.buffer) == bgfx_handle_type::index)
  {
    bgfx_set_index_buffer(
        to_handle<bgfx_index_buffer_handle_t>(drawcall.index.buffer),
        drawcall.index.first,
        drawcall.index.numIndices);
  }
  else
  {
    throw std::runtime_error("Invalid index buffer handle.");
  }

  if (bgfx_get_handle_type(drawcall.index.buffer) == bgfx_handle_type::dynamic_vertex)
  {
    bgfx_set_dynamic_vertex_buffer(
        drawcall.vertex.stream,
        to_handle<bgfx_dynamic_vertex_buffer_handle_t>(drawcall.vertex.buffer),
        drawcall.vertex.first,
        drawcall.vertex.numIndices);
  }
  else if (bgfx_get_handle_type(drawcall.index.buffer) == bgfx_handle_type::vertex)
  {
    bgfx_set_vertex_buffer(
        drawcall.vertex.stream,
        to_handle<bgfx_vertex_buffer_handle_t>(drawcall.vertex.buffer),
        drawcall.vertex.first,
        drawcall.vertex.numIndices);
  }
  else
  {
    throw std::runtime_error("Invalid vertex buffer handle.");
  }

  for (const auto uniform : drawcall.uniforms)
  {
    bgfx_set_uniform(uniform.handle, uniform.value, uniform.num);
  }

  bgfx_set_state(drawcall.state, drawcall.rgba);
  bgfx_submit(drawcall.view, drawcall.program, drawcall.depth, drawcall.preserve_state);
}
