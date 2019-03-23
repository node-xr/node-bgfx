#include "bgfx.h"

#include <node_api.h>
#include <bgfx/c99/bgfx.h>

napi_value create_addon(napi_env env)
{
  napi_value result;
  assert(napi_create_object(env, &result) == napi_ok);

  napi_value exported_function;
  assert(napi_create_function(env,
                              "doSomethingUseful",
                              NAPI_AUTO_LENGTH,
                              DoSomethingUseful,
                              NULL,
                              &exported_function) == napi_ok);
  assert(napi_set_named_property(env,
                                 result,
                                 "doSomethingUseful",
                                 exported_function) == napi_ok);

  return result;
}