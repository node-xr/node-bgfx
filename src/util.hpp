#pragma once
#include <node_api.h>

#define ASSERT_OK(_x, _err, _msg)        \
  {                                      \
    napi_status status = (_x);           \
    if (status != napi_ok)               \
    {                                    \
      napi_throw_error(env, _err, _msg); \
      return NULL;                       \
    }                                    \
  }

#define GET_ARGS(_x)                                        \
  {                                                         \
    size_t argc = (_x);                                     \
    napi_get_cb_info(env, info, &argc, argv, NULL, NULL);   \
    if (argc < (_x))                                        \
    {                                                       \
      napi_throw_error(env, "EINVAL", "Too few arguments"); \
      return NULL;                                          \
    }                                                       \
  }

napi_status napi_get_value_external_opt(napi_env env, napi_value value, void** result);
void export_function(napi_env env, napi_value exports, const char *name, napi_callback fn);
