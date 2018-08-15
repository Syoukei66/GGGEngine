#pragma once

#include "../Core/NativeType.h"

class RuntimeSetting
{
public:
  enum DebugFlag
  {
    CONVERTER_TEST = 1 << 0,
  };

private:
  static RuntimeSetting& GetInstance()
  {
    static RuntimeSetting self;
    return self;
  }
  RuntimeSetting() {}
  ~RuntimeSetting() {}

public:
  RuntimeSetting(const RuntimeSetting&) = delete;
  RuntimeSetting& operator=(const RuntimeSetting&) = delete;
  RuntimeSetting(RuntimeSetting&&) = delete;
  RuntimeSetting& operator=(RuntimeSetting&&) = delete;

public:
  inline static void SetDebugFlag(DebugFlag flag)
  {
    GetInstance().flags_ |= flag;
  }
  inline static void ResetDebugFlag(DebugFlag flag)
  {
    GetInstance().flags_ &= ~flag;
  }
  inline static bool CheckDebugFlag(DebugFlag flag)
  {
    return GetInstance().flags_ & flag;
  }

private:
  T_UINT32 flags_;

};