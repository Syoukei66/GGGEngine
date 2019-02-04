#include "WindowsPlatform.h"
#include <imgui/imgui.h>
#include <Native/Windows/imgui/imgui_impl_win32.h>

// =================================================================
// Methods from Platform
// =================================================================
bool WindowsPlatform::ContinueEnabled()
{
  return this->msg_.message != WM_QUIT;
}

bool WindowsPlatform::FrameEnabled()
{
  if (PeekMessage(&this->msg_, NULL, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&this->msg_);
    DispatchMessage(&this->msg_);
    return false;
  }
  return true;
}

void WindowsPlatform::ImGuiNewFrame()
{
  ImGui_ImplWin32_NewFrame();
}

// =================================================================
// Methods
// =================================================================
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WindowsPlatform::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
  if (uMsg == WM_CLOSE)
  {
    DestroyWindow(hWnd);
  }
  if (uMsg == WM_DESTROY)
  {
    PostQuitMessage(0);
  }
  if (uMsg == WM_KEYDOWN)
  {
    if (wParam == VK_ESCAPE)
    {
      if (MessageBox(hWnd, "�I�����܂����H", "�I���̂��m�点", MB_YESNO | MB_NOFOCUS) == IDYES)
      {
        DestroyWindow(hWnd);
      }
    }
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
