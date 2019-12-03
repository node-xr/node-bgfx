#pragma once
#include "bgfx_handle.hpp"
#include <bgfx/c99/bgfx.h>
#include <napi_bind.hpp>
#include <node_api.h>

struct bgfx_mat4_t
{
  float data[16];
};

struct bgfx_mat4_array_t
{
  bgfx_mat4_t *head;
  size_t count;
};

struct bgfx_texture_result_t
{
  bgfx_texture_handle_t handle;
  bgfx_texture_info_t info;
};

namespace napi_bind
{

//===========================================================================
template <>
inline const bgfx_memory_t *decode(napi_env env, napi_value value)
{
  void *ptr;
  size_t len;
  ok(env, napi_get_arraybuffer_info(env, value, &ptr, &len));
  return bgfx_copy(ptr, len);
}

//===========================================================================
template <typename T>
struct napi_bind::decoder<T, typename std::enable_if_t<bgfx_is_handle<T>()>>
{
  decoder(napi_env e, napi_value v) : env(e), value(v) {}

  T operator()()
  {
    uint32_t handle;
    ok(env, napi_get_value_uint32(env, value, &handle));
    return bgfx_unpack_handle<T>(handle);
  }

private:
  napi_env env;
  napi_value value;
};

template <typename T>
struct napi_bind::encoder<T, typename std::enable_if_t<bgfx_is_handle<T>()>>
{
  encoder(T v) : value(v) {}

  napi_value operator()(napi_env env)
  {
    uint32_t handle = bgfx_pack_handle<T>(value);

    napi_value result;
    ok(env, napi_create_uint32(env, handle, &result));
    return result;
  }

private:
  T value;
};

//===========================================================================
template <>
inline bgfx_mat4_t *decode(napi_env env, napi_value value)
{
  size_t n;
  bgfx_mat4_t *result;
  ok(env, napi_get_arraybuffer_info(env, value, reinterpret_cast<void **>(&result), &n));
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
  ok(env, napi_get_arraybuffer_info(env, value, reinterpret_cast<void **>(&ptr), &n));
  if (n % sizeof(bgfx_mat4_t))
    throw std::runtime_error("Matrix 4x4 array must have multiple of 16 float elements.");

  bgfx_mat4_array_t result;
  result.head = ptr;
  result.count = n / sizeof(bgfx_mat4_t);
  return result;
}

//===========================================================================
template <>
inline napi_value encode(napi_env env, bgfx_texture_info_t info)
{
  napi_value result;
  ok(env, napi_create_object(env, &result));

  encode_property<bgfx_texture_format_t>(env, result, "format", info.format);
  encode_property<uint32_t>(env, result, "storageSize", info.storageSize);
  encode_property<uint16_t>(env, result, "width", info.width);
  encode_property<uint16_t>(env, result, "height", info.height);
  encode_property<uint16_t>(env, result, "depth", info.depth);
  encode_property<uint16_t>(env, result, "numLayers", info.numLayers);
  encode_property<uint16_t>(env, result, "numMips", info.numMips);
  encode_property<uint8_t>(env, result, "bitsPerPixel", info.bitsPerPixel);
  encode_property<bool>(env, result, "cubeMap", info.cubeMap);

  return result;
}

//===========================================================================
template <>
inline napi_value encode(napi_env env, bgfx_texture_result_t texResult)
{
  napi_value result;
  ok(env, napi_create_object(env, &result));

  encode_property<bgfx_texture_handle_t>(env, result, "handle", texResult.handle);
  encode_property<bgfx_texture_info_t>(env, result, "info", texResult.info);

  return result;
}

} // namespace napi_bind
