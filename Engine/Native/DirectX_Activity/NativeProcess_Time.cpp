#include "NativeProcess_Time.h"

#define NOMINMAX
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <Director.h>

#ifdef _DEBUG
NativeProcess_Time::NativeProcess_Time()
  : fps_()
  , frame_time_()
  , time_start_()
  , time_end_()
  , time_freq_()
{}
#else
NativeProcess_Time::NativeProcess_Time()
{}
#endif


#ifdef _DEBUG
void NativeProcess_Time::FPS_Init()
{
  this->fps_ = Director::GetInstance()->GetFrameRate();
  QueryPerformanceFrequency(&this->time_freq_);
  QueryPerformanceCounter(&this->time_start_);
}

void NativeProcess_Time::FPS_PreUpdate()
{
  QueryPerformanceCounter(&this->time_end_);
  this->frame_time_ = static_cast<float>(this->time_end_.QuadPart - time_start_.QuadPart) / static_cast<float>(time_freq_.QuadPart);
}

void NativeProcess_Time::FPS_PostUpdate()
{
  this->fps_ = (this->fps_ * 0.99f) + (0.01f / this->frame_time_);
  this->time_start_ = this->time_end_;
}

T_FLOAT NativeProcess_Time::FPS_GetValue()
{
  return this->fps_;
}

#endif
