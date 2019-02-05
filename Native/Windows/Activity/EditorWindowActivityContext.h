#pragma once

#include "WindowsContext.h"
#include <Native/Windows/API/Graphics/DX9/DX9GraphicsAPI.h>

/*!
 * @brief WindowsのWindowハンドルをエディタウィンドウから受け取るアクティビティ
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