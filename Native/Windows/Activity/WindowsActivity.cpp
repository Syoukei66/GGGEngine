#include "WindowActivity.h"
#include <Core/Util/Logger.h>
#include <imgui/imgui.h>
#include <Native/Windows/imgui/imgui_impl_win32.h>

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
  if (PeekMessage(&this->msg_, NULL, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&this->msg_);
    DispatchMessage(&this->msg_);
    return false;
  }
  ImGui_ImplWin32_NewFrame();
  return true;
}
