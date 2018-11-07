#pragma once

#define NOMINMAX
#include <Windows.h>
#include <Core/Activity/Activity.h>

#ifdef GG_GRAPHICS_API_DX9
#include <Native/Windows/API/Graphics/DX9/DX9GraphicsAPI.h>
#else

#endif

class WindowsActivity : public Activity
{
public:
  static GG_INLINE SharedRef<WindowsActivity> GetInstance()
  {
    return SharedRef<WindowsActivity>::StaticCast(Platform::GetActivity());
  }

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_INIT_FUNC_1(WindowsActivity, const ActivityOption& option);
  GG_DESTRUCT_FUNC(WindowsActivity);

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
protected:
  virtual bool ContinueEnabled() override;
  virtual bool FrameEnabled() override;
  
  // =================================================================
  // Method
  // =================================================================
public:
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
#ifdef GG_GRAPHICS_API_DX9
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
        if (MessageBox(hWnd, "終了しますか？", "終了のお知らせ", MB_YESNO | MB_NOFOCUS) == IDYES)
        {
          DestroyWindow(hWnd);
        }
      }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE HWND GetWindowHandle() const
  {
    return this->wnd_;
  }
  
  // =================================================================
  // Data Member
  // =================================================================
private:
  HINSTANCE instance_;
  HWND wnd_;
  DWORD before_update_count_;
  RECT window_rect_;
  MSG msg_;
};