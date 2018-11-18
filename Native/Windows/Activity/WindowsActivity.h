#pragma once

#define NOMINMAX
#include <Windows.h>
#include <Core/Application/Activity/Activity.h>

class WindowsActivity : public Activity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_INIT_FUNC_2(WindowsActivity, const ActivityOption&, HWND);

  // =================================================================
  // Methods from Activity
  // =================================================================
protected:
  virtual bool ContinueEnabled() override;
  virtual bool FrameEnabled() override;
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