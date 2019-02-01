#include "WindowsContext.h"
#include <Core/Util/Logger.h>

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
bool WindowsContext::IsActive()
{
  return this->window_handle_ == GetForegroundWindow();
}
