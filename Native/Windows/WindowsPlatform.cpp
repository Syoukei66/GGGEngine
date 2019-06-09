#include "WindowsPlatform.h"
#include <imgui/imgui.h>
#include <Native/Windows/imgui/imgui_impl_win32.h>
// =================================================================
// GGG Statement
// =================================================================
GG_CREATE_FUNC_IMPL(WindowsPlatform)
{
  return true;
}

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
  const SharedRef<Activity>& activity = Application::GetActivity((T_UINT64)hWnd);
  if (uMsg == WM_CLOSE)
  {
    // メインアクティビティなら終了、そうでなければ非表示に
    if (activity && !activity->GetContext().GetOption().sub_window)
    {
      DestroyWindow(hWnd);
    }
    else
    {
      ShowWindow(hWnd, SW_HIDE);
      return 0;
    }
  }
  if (uMsg == WM_DESTROY)
  {
    // サブウィンドウではないウィンドウが終了したら
    // アプリケーション終了
    if (activity && !activity->GetContext().GetOption().sub_window)
    {
      PostQuitMessage(0);
    }
  }
  if (uMsg == WM_KEYDOWN)
  {
    if (wParam == VK_ESCAPE)
    {
      if (MessageBox(hWnd, "終了しますか？", "終了のお知らせ", MB_YESNO | MB_NOFOCUS) == IDYES)
      {
        DestroyWindow((HWND)Application::GetMainActivity()->GetContext().GetActivityID());
      }
    }
  }  
  if (activity)
  {
    ImGuiContext* context = ImGui::GetCurrentContext();
    ImGui::SetCurrentContext(activity->GetContext().GetImGuiContext().get());
    ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
    ImGui::SetCurrentContext(context);
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
