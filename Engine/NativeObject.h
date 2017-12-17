#pragma once

#include "NativeType.h"

class NativeObject
{
protected:
  NativeObject(LP_NATIVE_INSTANCE instance);

public:
  ~NativeObject() {}

public:
  inline LP_NATIVE_INSTANCE GetNativeObj() const
  {
    return this->instance_;
  }

protected:
  LP_NATIVE_INSTANCE instance_;
};