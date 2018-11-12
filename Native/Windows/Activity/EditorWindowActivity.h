#pragma once

#include "WindowsActivity.h"
#include <Native/Windows/API/Graphics/DX9/DX9GraphicsAPI.h>

/*!
 * @brief WindowsのWindowハンドルをエディタウィンドウから受け取るアクティビティ
 */
class EditorWindowActivity : public WindowsActivity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(EditorWindowActivity);
  GG_CREATE_FUNC_2(EditorWindowActivity, const ActivityOption&, HWND);

};