#include "util.hpp"
#include <string>

napi_status napi_get_value_external_opt(napi_env env, napi_value value, void** result)
{
  napi_status status;
  napi_valuetype type;

  // Check if this argument is set to null.
  status = napi_typeof(env, value, &type);
  if (status != napi_ok) return status;

  if (type == napi_null) {
    // If null was provided, fill in a null-pointer.
    *result = nullptr;
    return napi_ok;
  } else {
    // Otherwise, load the actual external pointer.
    status = napi_get_value_external(env, value, result);
    return status;
  }
}

void export_function(napi_env env, napi_value exports, const char *name, napi_callback fn)
{
  napi_status status = napi_ok;
  napi_value exported_fn = nullptr;

  status = napi_create_function(env, name, NAPI_AUTO_LENGTH, fn, NULL, &exported_fn);
  if (status != napi_ok)
  {
    std::string message("Unable to wrap native function: ");
    message += name;
    napi_throw_error(env, NULL, message.c_str());
  }

  status = napi_set_named_property(env, exports, name, exported_fn);
  if (status != napi_ok)
  {
    std::string message("Unable to populate exports with: ");
    message += name;
    napi_throw_error(env, NULL, message.c_str());
  }
}