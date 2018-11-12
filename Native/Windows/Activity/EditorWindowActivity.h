#pragma once

#include "WindowsActivity.h"
#include <Native/Windows/API/Graphics/DX9/DX9GraphicsAPI.h>

/*!
 * @brief Windows��Window�n���h�����G�f�B�^�E�B���h�E����󂯎��A�N�e�B�r�e�B
 */
class EditorWindowActivity : public WindowsActivity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(EditorWindowActivity);
  GG_CREATE_FUNC_2(EditorWindowActivity, const ActivityOption&, HWND);

};