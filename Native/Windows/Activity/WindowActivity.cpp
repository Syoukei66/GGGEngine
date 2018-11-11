#include "WindowActivity.h"

#include <windowsx.h>

#include <Core/Application/Activity/ActivityOption.h>
#include <imgui/imgui.h>
#include <Native/Windows/imgui/imgui_impl_win32.h>

// =================================================================
// GGG Statement
// =================================================================
static HWND CreateWindowWithActivityOption(const ActivityOption& option)
{
  HINSTANCE instance = GetModuleHandle(NULL);

  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_VREDRAW | CS_HREDRAW | CS_CLASSDC;
  wcex.lpfnWndProc = WindowActivity::WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = instance;
  wcex.hIcon = NULL;
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = option.activity_name;
  wcex.hIconSm = NULL;

  RegisterClassEx(&wcex);
  DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX;
  RECT wr = { 0, 0, (LONG)option.window_size.width, (LONG)option.window_size.height };

  AdjustWindowRectEx(&wr, windowStyle, false, 0);
  int windowWidth = wr.right - wr.left;
  int windowHeight = wr.bottom - wr.top;

  RECT dr;
  GetWindowRect(GetDesktopWindow(), &dr);

  int desktopWidth = dr.right - dr.left;
  int desktopHeight = dr.bottom - dr.top;
  int windowX = desktopWidth < windowWidth ? 0 : (desktopWidth - windowWidth) >> 1;
  int windowY = desktopHeight < windowHeight ? 0 : (desktopHeight - windowHeight) >> 1;

  HWND hwnd = CreateWindowEx(
    0,				//�g���E�B���h�E�X�^�C��
    option.activity_name,	//�o�^����Ă���N���X��
    option.activity_name,	//�E�B���h�E��
    windowStyle,	//�E�B���h�E�X�^�C��
    windowX,	//�E�B���h�E�������̈ʒu
    windowY,	//�E�B���h�E�c�����̈ʒu
    windowWidth,	//�E�B���h�E�̕�
    windowHeight,	//�E�B���h�E�̍���
    NULL,		//�e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
    NULL,		//���j���[�n���h���܂��͎q���ʎq
    instance,	//�A�v���P�[�V�����C���X�^���X�̃n���h��
    NULL		//�E�B���h�E�쐬�f�[�^
  );
  ShowWindow(hwnd, SW_SHOWDEFAULT);
  UpdateWindow(hwnd);

  //imgui initialize
  ImGui_ImplWin32_Init(hwnd);

  return hwnd;
}

GG_INIT_FUNC_IMPL_1(WindowActivity, const ActivityOption& option)
{
  //imgui uninitialize
  ImGui_ImplWin32_Shutdown();
  return WindowsActivity::Init(option, CreateWindowWithActivityOption(option));
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WindowActivity::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
