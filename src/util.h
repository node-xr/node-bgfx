#pragma once

#include <bgfx/c99/bgfx.h>
#include <nan.h>
#include <v8.h>

//=============================================================================
/// Template conversion function from C++ to Node.
template <typename T>
v8::Local<v8::Value> encode(const T &value);

/// Template conversion function from Node to C++.
template <typename T>
T decode(const v8::Local<v8::Value>);

//=============================================================================
template <typename T>
v8::Local<v8::Value> encodeHandle(const T &handle)
{
  Nan::EscapableHandleScope scope;
  auto result = Nan::New<v8::Number>(handle.idx);
  return scope.Escape(result);
}

template <typename T>
T decodeHandle(v8::Local<v8::Value> value)
{
  T result;
  result.idx = value->NumberValue();
  return result;
}
