#pragma once

#define NOMINMAX
#include <windows.h>
#include <INativeProcess_Time.h>

class NativeProcess_Time : public INativeProcess_Time
{
#ifdef _DEBUG
public:
  NativeProcess_Time();
#else
public:
  NativeProcess_Time();
#endif

#ifdef _DEBUG
public:
  virtual void FPS_Init() override;
  virtual void FPS_PreUpdate() override;
  virtual void FPS_PostUpdate() override;
  virtual T_FLOAT FPS_GetValue() override;
#endif

#ifdef _DEBUG
public:
  T_FLOAT fps_;
  T_FLOAT frame_time_;
  LARGE_INTEGER time_start_;
  LARGE_INTEGER time_end_;
  LARGE_INTEGER time_freq_;
#endif

};
