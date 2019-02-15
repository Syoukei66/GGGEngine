#pragma once

#include "WindowsContext.h"
#include <Native/Windows/API/Graphics/DX9/DX9GraphicsAPI.h>

/*!
 * @brief Windows��Window�n���h�����G�f�B�^�E�B���h�E����󂯎��A�N�e�B�r�e�B
 */
class EditorWindowActivityContext : public WindowsContext
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
  EditorWindowActivityContext(HWND hwnd);

  // =================================================================
  // Methods from ActivityContext
  // =================================================================
protected:
  virtual void OnStart(const ActivityOption& option) override;
  virtual void OnEnd() override;

};