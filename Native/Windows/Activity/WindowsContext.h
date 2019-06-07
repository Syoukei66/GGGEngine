#pragma once

#define NOMINMAX
#include <Windows.h>
#include <Core/Application/Activity/ActivityContext.h>

class WindowsContext : public ActivityContext
{
  // =================================================================
  // Methods from ActivityContext
  // =================================================================
protected:
  virtual void OnNewFrame() override;
  virtual void OnShow() override;
  virtual void OnHide() override;

  virtual bool IsActive() const override;
  virtual bool IsVisible() const override;
  virtual bool IsEnabled() const override;
  virtual T_UINT64 GetActivityID() const
  {
    return (T_UINT64)this->window_handle_;
  }

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