#pragma once

#include "WindowsActivity.h"

/*!
 * @brief Windows��Window������쐬����A�N�e�B�r�e�B
 */
class WindowActivity : public WindowsActivity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(WindowActivity);
  GG_CREATE_FUNC_1(WindowActivity, const ActivityOption&);

  // =================================================================
  // Method
  // =================================================================
public:
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};