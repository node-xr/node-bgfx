#pragma once
#include <cstring>
#include <node_api.h>
#include <type_traits>
#include <vector>

namespace wrap
{

//===========================================================================
template <>
inline std::string decode(napi_env env, napi_value value)
{
  constexpr size_t buffer_len = 2048;
  std::string result;
  result.reserve(buffer_len);

  // FIXME: this is probably unsafe behavior.
  size_t result_len;
  ok(napi_get_value_string_utf8(env, value, const_cast<char *>(result.data()), buffer_len, &result_len));
  result.resize(result_len);

  return result;
}

template <>
inline napi_value encode(napi_env env, const std::string &value)
{
  napi_value result;
  ok(napi_create_string_utf8(env, value.c_str(), value.length(), &result));
  return result;
}

//===========================================================================
template <>
inline const char *decode(napi_env env, napi_value value)
{
  constexpr size_t buffer_len = 2048;
  char *leaky_buffer = new char[buffer_len];

  // FIXME: this is 100% wrong behavior.
  size_t result_len;
  ok(napi_get_value_string_utf8(env, value, leaky_buffer, buffer_len, &result_len));
  return leaky_buffer;
}

template <>
inline napi_value encode(napi_env env, const char *value)
{
  napi_value result;
  if (value)
  {
    ok(napi_create_string_utf8(env, value, strlen(value), &result));
  }
  else
  {
    ok(napi_get_null(env, &result));
  }
  return result;
}

//===========================================================================
template <>
inline bool decode(napi_env env, napi_value value)
{
  bool result;
  ok(napi_get_value_bool(env, value, &result));
  return result;
}

template <>
inline napi_value encode(napi_env env, const bool value)
{
  napi_value result;
  ok(napi_get_boolean(env, value, &result));
  return result;
}

//===========================================================================
template <>
inline uint8_t decode(napi_env env, napi_value value)
{
  uint32_t result;
  ok(napi_get_value_uint32(env, value, &result));
  return static_cast<uint8_t>(result);
}

template <>
inline napi_value encode(napi_env env, const uint8_t value)
{
  napi_value result;
  ok(napi_create_uint32(env, static_cast<uint32_t>(value), &result));
  return result;
}

//===========================================================================
template <>
inline uint16_t decode(napi_env env, napi_value value)
{
  uint32_t result;
  ok(napi_get_value_uint32(env, value, &result));
  return static_cast<uint16_t>(result);
}

template <>
inline napi_value encode(napi_env env, const uint16_t value)
{
  napi_value result;
  ok(napi_create_uint32(env, static_cast<uint16_t>(value), &result));
  return result;
}

//===========================================================================
template <>
inline uint32_t decode(napi_env env, napi_value value)
{
  uint32_t result;
  ok(napi_get_value_uint32(env, value, &result));
  return result;
}

template <>
inline napi_value encode(napi_env env, const uint32_t value)
{
  napi_value result;
  ok(napi_create_uint32(env, value, &result));
  return result;
}

//===========================================================================
template <>
inline int32_t decode(napi_env env, napi_value value)
{
  int32_t result;
  ok(napi_get_value_int32(env, value, &result));
  return result;
}

template <>
inline napi_value encode(napi_env env, const int32_t value)
{
  napi_value result;
  ok(napi_create_int32(env, value, &result));
  return result;
}

//===========================================================================
template <>
inline int64_t decode(napi_env env, napi_value value)
{
  int64_t result;
  bool lossless;
  ok(napi_get_value_bigint_int64(env, value, &result, &lossless));
  if (!lossless)
    throw new std::runtime_error("BigInt to Int64 conversion loss.");
  return result;
}

template <>
inline napi_value encode(napi_env env, const int64_t value)
{
  napi_value result;
  ok(napi_create_bigint_int64(env, value, &result));
  return result;
}

//===========================================================================
template <>
inline uint64_t decode(napi_env env, napi_value value)
{
  uint64_t result;
  bool lossless;
  ok(napi_get_value_bigint_uint64(env, value, &result, &lossless));
  if (!lossless)
    throw new std::runtime_error("BigInt to Uint64 conversion loss.");
  return result;
}

template <>
inline napi_value encode(napi_env env, const uint64_t value)
{
  napi_value result;
  ok(napi_create_bigint_uint64(env, value, &result));
  return result;
}

//===========================================================================
// Default for unmanaged pointer types.
template <typename T>
struct decoder<T, typename std::enable_if_t<std::is_pointer<T>::value>>
{
  static T eval(napi_env env, napi_value value)
  {
    void *result;
    ok(napi_get_value_external_opt(env, value, &result));
    return static_cast<T>(result);
  }
};

template <typename T>
struct encoder<T, typename std::enable_if_t<std::is_pointer<T>::value>>
{
  static napi_value eval(napi_env env, T value)
  {
    napi_value result;
    // For a default pointer handler, assume memory is not owned.
    napi_create_external_opt(env, static_cast<void *>(value), nullptr, nullptr, &result);
    return result;
  }
};

//===========================================================================
// Default for floating-point types.
template <typename T>
struct decoder<T, typename std::enable_if_t<std::is_floating_point<T>::value>>
{
  static T eval(napi_env env, napi_value value)
  {
    double result;
    ok(napi_get_value_double(env, value, &result));
    return static_cast<T>(result);
  }
};

template <typename T>
struct encoder<T, typename std::enable_if_t<std::is_floating_point<T>::value>>
{
  static napi_value eval(napi_env env, T value)
  {
    napi_value result;
    ok(napi_create_double(env, static_cast<double>(value), &result));
    return result;
  }
};

//===========================================================================
// Default for enum types.
template <typename T>
struct decoder<T, typename std::enable_if_t<std::is_enum<T>::value>>
{
  static T eval(napi_env env, napi_value value)
  {
    uint32_t result;
    ok(napi_get_value_uint32(env, value, &result));
    return static_cast<T>(result);
  }
};

template <typename T>
struct encoder<T, typename std::enable_if_t<std::is_enum<T>::value>>
{
  static napi_value eval(napi_env env, T value)
  {
    napi_value result;
    ok(napi_create_uint32(env, static_cast<uint32_t>(value), &result));
    return result;
  }
};

//===========================================================================
// Default for container types.
// Based on: https://stackoverflow.com/a/31207079
template <typename T, typename _ = void>
struct is_container : std::false_type
{
};

template <typename T>
struct is_container<
    T,
    std::conditional_t<
        false,
        std::void_t<
            typename T::value_type,
            typename T::size_type,
            typename T::allocator_type,
            typename T::iterator,
            typename T::const_iterator,
            decltype(std::declval<T>().size()),
            decltype(std::declval<T>().begin()),
            decltype(std::declval<T>().end()),
            decltype(std::declval<T>().cbegin()),
            decltype(std::declval<T>().cend())>,
        void>> : public std::true_type
{
};

template <typename T>
struct encoder<T, typename std::enable_if_t<is_container<T>::value>>
{
  static napi_value eval(napi_env env, T value)
  {
    napi_value result;
    constexpr size_t len = value.size();
    ok(napi_create_array_with_length(env, len, &result));

    size_t idx = 0;
    for (const auto &element : value)
    {
      ok(napi_set_element(env, result, idx++, encode<T>(env, element)));
    }

    return result;
  }
};

//===========================================================================
// Default for std::vector.
template <typename T>
struct is_std_vector : std::false_type
{
};

template <typename T>
struct is_std_vector<std::vector<T>> : public std::true_type
{
};

template <typename T>
struct decoder<T, typename std::enable_if_t<is_std_vector<T>::value>>
{
  static T eval(napi_env env, napi_value value)
  {
    using element_t = typename T::value_type;

    uint32_t len;
    ok(napi_get_array_length(env, value, &len));

    T result(len);
    for (size_t idx = 0; idx < len; ++idx)
    {
      napi_value element;
      ok(napi_get_element(env, value, idx, &element));
      result[idx] = decode<element_t>(env, element);
    }
    return result;
  }
};

} // namespace wrap
