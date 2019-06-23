#pragma once
#include "wrap.hpp"
#include <bgfx/c99/bgfx.h>
#include <node_api.h>
#include "bgfx_handle.hpp"

struct bgfx_mat4_t
{
  float data[16];
};

struct bgfx_mat4_array_t
{
  bgfx_mat4_t *head;
  size_t count;
};

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
template <typename T>
struct decoder<T, typename std::enable_if_t<bgfx_is_handle<T>()>>
{
  static T eval(napi_env env, napi_value value)
  {
    uint32_t handle;
    ok(napi_get_value_uint32(env, value, &handle));
    return bgfx_unpack_handle<T>(handle);
  }
};

template <typename T>
struct encoder<T, typename std::enable_if_t<bgfx_is_handle<T>()>>
{
  static napi_value eval(napi_env env, T value)
  {
    uint32_t handle = bgfx_pack_handle<T>(value);

    napi_value result;
    ok(napi_create_uint32(env, handle, &result));
    return result;
  }
};

//===========================================================================
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
// TODO: this is the wrong direction for the conversion.
// This should be an output parameter.
template <>
inline bgfx_texture_info_t decode(napi_env env, napi_value value)
{
  bgfx_texture_info_t result;
  result.format = decode_property<bgfx_texture_format_t>(env, value, "format");
  result.storageSize = decode_property<uint32_t>(env, value, "storageSize");
  result.width = decode_property<uint16_t>(env, value, "width");
  result.height = decode_property<uint16_t>(env, value, "height");
  result.depth = decode_property<uint16_t>(env, value, "depth");
  result.numLayers = decode_property<uint16_t>(env, value, "numLayers");
  result.numMips = decode_property<uint8_t>(env, value, "numMips");
  result.bitsPerPixel = decode_property<uint8_t>(env, value, "bitsPerPixel");
  result.cubeMap = decode_property<bool>(env, value, "cubeMap");
  return result;
}

} // namespace wrap
