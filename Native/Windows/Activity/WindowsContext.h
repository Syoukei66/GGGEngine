#pragma once

#define NOMINMAX
#include <Windows.h>
#include <Core/Application/Activity/ActivityContext.h>

class WindowsContext : public ActivityContext
{
  // =================================================================
  // GGG Statement
  // =================================================================
public:
  GG_INIT_FUNC_1(WindowsContext, HWND);

  // =================================================================
  // Methods from Activity
  // =================================================================
protected:
  virtual bool IsActive() override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE HWND GetWindowHandle() const
  {
    return this->window_handle_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  HWND window_handle_;
  MSG msg_;

};