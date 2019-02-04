#include "WindowsContext.h"
#include <Core/Util/Logger.h>
#include <Native/Windows/imgui/imgui_impl_win32.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(WindowsContext, HWND hwnd)
{
  this->window_handle_ = hwnd;
  return true;
}

// =================================================================
// Methods from Activity
// =================================================================
void WindowsContext::OnNewFrame()
{
  //imgui initialize
  ImGui_ImplWin32_Init(this->window_handle_);
}

bool WindowsContext::IsActive() const
{
  return this->window_handle_ == GetForegroundWindow();
}

bool WindowsContext::IsVisible() const
{
  return IsWindowVisible(this->window_handle_);
}

bool WindowsContext::IsEnabled() const
{
  return IsWindow(this->window_handle_);
}
