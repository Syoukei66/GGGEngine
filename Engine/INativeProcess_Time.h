#pragma once

#include "NativeType.h"

class INativeProcess_Time
{
public:

#ifdef _DEBUG
public:
  virtual void FPS_Init() = 0;
  virtual void FPS_PreUpdate() = 0;
  virtual void FPS_PostUpdate() = 0;
  virtual T_FLOAT FPS_GetValue() = 0;
#endif

};