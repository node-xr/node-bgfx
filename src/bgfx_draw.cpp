#include "bgfx_draw.hpp"
#include "bgfx_converters.hpp"
#include <iostream>

const std::vector<bgfx_uniform_args_t> EMPTY_UNIFORMS;
const bgfx_mat4_t IDENTITY_MATRIX = {{1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1}};

constexpr size_t uniform_size(bgfx_uniform_type_t type)
{
  switch (type)
  {
  case BGFX_UNIFORM_TYPE_SAMPLER:
    return sizeof(bgfx_texture_handle_t);
  case BGFX_UNIFORM_TYPE_VEC4:
    return sizeof(float) * 4;
  case BGFX_UNIFORM_TYPE_MAT3:
    return sizeof(float) * 9;
  case BGFX_UNIFORM_TYPE_MAT4:
    return sizeof(float) * 9;
  default:
    throw std::runtime_error("Unsupported uniform type.");
  }
}

namespace wrap
{

template <>
inline bgfx_index_buffer_args_t decode(napi_env env, napi_value value)
{
  bgfx_index_buffer_args_t result;

  napi_valuetype type;
  ok(napi_typeof(env, value, &type));

  if (type == napi_object)
  {
    result.buffer = decode_property<uint32_t>(env, value, "buffer");
    result.first = decode_property<uint32_t>(env, value, "first", 0);
    result.numIndices = decode_property<uint32_t>(env, value, "numIndices", UINT32_MAX);
  }
  else if (type == napi_number)
  {
    result.buffer = decode<uint32_t>(env, value);
    result.first = 0;
    result.numIndices = UINT32_MAX;
  }
  else
  {
    throw std::runtime_error("Invalid index buffer.");
  }

  return result;
}

template <>
inline bgfx_vertex_buffer_args_t decode(napi_env env, napi_value value)
{
  bgfx_vertex_buffer_args_t result;

  napi_valuetype type;
  ok(napi_typeof(env, value, &type));

  if (type == napi_object)
  {
    result.stream = decode_property<uint8_t>(env, value, "stream", 0);
    result.buffer = decode_property<uint32_t>(env, value, "buffer");
    result.first = decode_property<uint32_t>(env, value, "first", 0);
    result.numIndices = decode_property<uint32_t>(env, value, "numIndices", UINT32_MAX);
  }
  else if (type == napi_number)
  {
    result.stream = 0;
    result.buffer = decode<uint32_t>(env, value);
    result.first = 0;
    result.numIndices = UINT32_MAX;
  }
  else
  {
    throw std::runtime_error("Invalid vertex buffer.");
  }

  return result;
}

template <>
inline std::vector<bgfx_uniform_args_t> decode(napi_env env, napi_value value)
{
  napi_value handles;
  ok(napi_get_property_names(env, value, &handles));
  // TODO: is retrieving this a performance problem?

  uint32_t num_uniforms;
  ok(napi_get_array_length(env, handles, &num_uniforms));

  std::vector<bgfx_uniform_args_t> result(num_uniforms);
  for (uint32_t idx = 0; idx < num_uniforms; ++idx)
  {
    bgfx_uniform_args_t uniform;

    napi_value handle;
    ok(napi_get_element(env, handles, idx, &handle));
    uniform.handle = decode<bgfx_uniform_handle_t>(env, handle);

    bgfx_uniform_info_t info;
    bgfx_get_uniform_info(uniform.handle, &info);
    const auto element_size = uniform_size(info.type);

    napi_value buffer;
    ok(napi_get_property(env, value, handle, &buffer));

    size_t element_len;
    ok(napi_get_arraybuffer_info(env, buffer, &uniform.value, &element_len));

    uniform.num = element_len / element_size;
    result[idx] = uniform;
  }

  return result;
}

template <>
inline std::vector<bgfx_texture_args_t> decode(napi_env env, napi_value value)
{
  napi_value handles;
  ok(napi_get_property_names(env, value, &handles));
  // TODO: is retrieving this a performance problem?

  uint32_t num_textures;
  ok(napi_get_array_length(env, handles, &num_textures));

  std::vector<bgfx_texture_args_t> result(num_textures);
  for (uint32_t idx = 0; idx < num_textures; ++idx)
  {
    bgfx_texture_args_t args;

    napi_value handle;
    ok(napi_get_element(env, handles, idx, &handle));
    args.handle = decode<bgfx_uniform_handle_t>(env, handle);

    napi_value props;
    ok(napi_get_property(env, value, handle, &props));
    args.stage = decode_property<uint8_t>(env, props, "stage");
    args.texture = decode_property<bgfx_texture_handle_t>(env, props, "texture");
    args.flags = decode_property<uint32_t>(env, props, "flags", 0);

    result[idx] = args;
  }

  return result;
}

template <>
bgfx_drawcall_t decode(napi_env env, napi_value value)
{
  bgfx_drawcall_t result;
  result.xform = decode_property<bgfx_mat4_t *>(env, value, "xform", const_cast<bgfx_mat4_t *>(&IDENTITY_MATRIX));
  result.state = decode_property<uint64_t>(env, value, "state", BGFX_STATE_DEFAULT);
  result.rgba = decode_property<uint32_t>(env, value, "rgba", 0);
  result.depth = decode_property<uint32_t>(env, value, "depth", 0);
  result.index = decode_property_opt<bgfx_index_buffer_args_t>(env, value, "index");
  result.vertex = decode_property_opt<bgfx_vertex_buffer_args_t>(env, value, "vertex");
  result.uniforms = decode_property<std::vector<bgfx_uniform_args_t>>(env, value, "uniforms", EMPTY_UNIFORMS);
  result.view = decode_property<bgfx_view_id_t>(env, value, "view");
  result.program = decode_property<bgfx_program_handle_t>(env, value, "program");
  result.preserve_state = decode_property<bool>(env, value, "preserve_state", false);
  return result;
}

} // namespace wrap

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
