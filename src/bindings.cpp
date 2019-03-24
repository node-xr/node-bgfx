#include "bgfx.h"

#include <node_api.h>

static napi_value Init(napi_env env, napi_value exports)
{
  return create_bgfx(env);
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)