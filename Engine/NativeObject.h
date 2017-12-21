#pragma once

<<<<<<< HEAD
template<typename T>
class NativeObject
{
public:
  NativeObject(T* native_instance)
    : instance_(native_instance)
  {}

public:
  inline T* GetNativeInstance()
  {
    return instance_;
  }

private:
  T* instance_;
=======
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
>>>>>>> parent of 4f2c2e8... NativeMatrixクラスの作成
};