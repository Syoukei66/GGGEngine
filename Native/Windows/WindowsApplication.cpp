#include "stdafx.h"
#include "WindowsApplication.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WindowsApplication::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
      if (MessageBox(hWnd, "終了しますか？", "終了のお知らせ", MB_YESNO | MB_NOFOCUS) == IDYES)
      {
        DestroyWindow(hWnd);
      }
    }
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
