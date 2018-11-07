#include "WindowsActivity.h"

#include <windowsx.h>

#include <Core/Activity/ActivityOption.h>

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
GG_INIT_FUNC_IMPL_1(WindowsActivity, const ActivityOption& option)
{
  Activity::Init(option);

  WNDCLASSEX wcex;

  this->instance_ = GetModuleHandle(NULL);

  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_VREDRAW | CS_HREDRAW | CS_CLASSDC;
  wcex.lpfnWndProc = this->WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = this->instance_;
  wcex.hIcon = NULL;
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = option.activity_name;
  wcex.hIconSm = NULL;

  RegisterClassEx(&wcex);
  DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX;
  RECT wr = { 0, 0, (LONG)option.window_size.width, (LONG)option.window_size.height };
  this->window_rect_ = wr;

  AdjustWindowRectEx(&wr, windowStyle, false, 0);
  int windowWidth = wr.right - wr.left;
  int windowHeight = wr.bottom - wr.top;

  RECT dr;
  GetWindowRect(GetDesktopWindow(), &dr);

  int desktopWidth = dr.right - dr.left;
  int desktopHeight = dr.bottom - dr.top;
  int windowX = desktopWidth < windowWidth ? 0 : (desktopWidth - windowWidth) >> 1;
  int windowY = desktopHeight < windowHeight ? 0 : (desktopHeight - windowHeight) >> 1;

  this->wnd_ = CreateWindowEx(
    0,				//拡張ウィンドウスタイル
    option.activity_name,	//登録されているクラス名
    option.activity_name,	//ウィンドウ名
    windowStyle,	//ウィンドウスタイル
    windowX,	//ウィンドウ横方向の位置
    windowY,	//ウィンドウ縦方向の位置
    windowWidth,	//ウィンドウの幅
    windowHeight,	//ウィンドウの高さ
    NULL,		//親ウィンドウまたはオーナーウィンドウのハンドル
    NULL,		//メニューハンドルまたは子識別子
    this->instance_,	//アプリケーションインスタンスのハンドル
    NULL		//ウィンドウ作成データ
  );
  ShowWindow(this->wnd_, SW_SHOWDEFAULT);
  UpdateWindow(this->wnd_);
  
  return true;
}

GG_DESTRUCT_FUNC_IMPL(WindowsActivity)
{
  return true;
}

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
  return true;
}
