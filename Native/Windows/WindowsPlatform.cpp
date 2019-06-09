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
    // ���C���A�N�e�B�r�e�B�Ȃ�I���A�����łȂ���Δ�\����
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
    // �T�u�E�B���h�E�ł͂Ȃ��E�B���h�E���I��������
    // �A�v���P�[�V�����I��
    if (activity && !activity->GetContext().GetOption().sub_window)
    {
      PostQuitMessage(0);
    }
  }
  if (uMsg == WM_KEYDOWN)
  {
    if (wParam == VK_ESCAPE)
    {
      if (MessageBox(hWnd, "�I�����܂����H", "�I���̂��m�点", MB_YESNO | MB_NOFOCUS) == IDYES)
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
