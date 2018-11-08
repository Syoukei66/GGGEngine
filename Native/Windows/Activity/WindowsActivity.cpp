#include "WindowActivity.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_2(WindowsActivity, const ActivityOption& option, HWND hwnd)
{
  Activity::Init(option);
  this->window_handle_ = hwnd;
  return true;
}

// =================================================================
// Methods from Activity
// =================================================================
bool WindowsActivity::ContinueEnabled()
{
  return this->msg_.message != WM_QUIT;
}

bool WindowsActivity::FrameEnabled()
{
  if (PeekMessage(&this->msg_, this->window_handle_, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&this->msg_);
    DispatchMessage(&this->msg_);
    return false;
  }
  return true;
}
