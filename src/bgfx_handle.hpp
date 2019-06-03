#pragma once
#include <bgfx/c99/bgfx.h>
#include <stdexcept>

enum class bgfx_handle_type : uint16_t
{
  invalid = 0x00,
  dynamic_index_buffer,
  dynamic_vertex_buffer,
  frame_buffer,
  index_buffer,
  indirect_buffer,
  occlusion_query,
  program,
  shader,
  texture,
  uniform,
  vertex_buffer,
};

template <typename T>
constexpr bgfx_handle_type bgfx_to_handle_type()
{
  if (std::is_same<T, bgfx_dynamic_index_buffer_handle_t>::value)
    return bgfx_handle_type::dynamic_index_buffer;
  else if (std::is_same<T, bgfx_dynamic_vertex_buffer_handle_t>::value)
    return bgfx_handle_type::dynamic_vertex_buffer;
  else if (std::is_same<T, bgfx_frame_buffer_handle_t>::value)
    return bgfx_handle_type::dynamic_index_buffer;
  else if (std::is_same<T, bgfx_index_buffer_handle_t>::value)
    return bgfx_handle_type::index_buffer;
  else if (std::is_same<T, bgfx_indirect_buffer_handle_t>::value)
    return bgfx_handle_type::indirect_buffer;
  else if (std::is_same<T, bgfx_occlusion_query_handle_t>::value)
    return bgfx_handle_type::occlusion_query;
  else if (std::is_same<T, bgfx_program_handle_t>::value)
    return bgfx_handle_type::program;
  else if (std::is_same<T, bgfx_shader_handle_t>::value)
    return bgfx_handle_type::shader;
  else if (std::is_same<T, bgfx_texture_handle_t>::value)
    return bgfx_handle_type::texture;
  else if (std::is_same<T, bgfx_uniform_handle_t>::value)
    return bgfx_handle_type::uniform;
  else if (std::is_same<T, bgfx_vertex_buffer_handle_t>::value)
    return bgfx_handle_type::vertex_buffer;
  else
    return bgfx_handle_type::invalid;
}

template <typename T>
constexpr bool bgfx_is_handle()
{
  return bgfx_to_handle_type<T>() != bgfx_handle_type::invalid;
}

constexpr bgfx_handle_type bgfx_get_handle_type(uint32_t value)
{
  return static_cast<bgfx_handle_type>(value >> 16);
}

//===========================================================================
template <typename T>
uint32_t bgfx_pack_handle(T handle)
{
  constexpr uint32_t type = static_cast<uint32_t>(bgfx_to_handle_type<T>());
  return handle.idx + (type << 16);
}

template <typename T>
T bgfx_unpack_handle(uint32_t value)
{
  constexpr uint32_t type = static_cast<uint32_t>(bgfx_to_handle_type<T>());
  if (type != value >> 16)
    throw std::runtime_error("Mismatched handle type");

  return {static_cast<uint16_t>(value)};
}
