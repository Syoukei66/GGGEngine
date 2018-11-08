#pragma once

#include <Native/Windows/API/Graphics/WindowsGraphicsAPI.h>

#include "WindowsActivity.h"

/*!
 * @brief Windows��Window������쐬����A�N�e�B�r�e�B
 */
class WindowActivity : public WindowsActivity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT_NAME(WindowActivity);
  GG_CREATE_FUNC_1(WindowActivity, const ActivityOption&);

  // =================================================================
  // Method
  // =================================================================
public:
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
#if GG_GRAPHICS_API_DX9
    DX9GraphicsAPI::WndProc(hWnd, uMsg, wParam, lParam);
#else
    GG_ASSERT_NO_ENTRY();
#endif
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

};