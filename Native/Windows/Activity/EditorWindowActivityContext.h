#pragma once

#include "WindowsContext.h"
#include <Native/Windows/API/Graphics/DX9/DX9GraphicsAPI.h>

/*!
 * @brief WindowsのWindowハンドルをエディタウィンドウから受け取るアクティビティ
 */
class EditorWindowActivityContext : public WindowsContext
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(EditorWindowActivityContext);
  GG_CREATE_FUNC_1(EditorWindowActivityContext, HWND);

  // =================================================================
  // Methods from ActivityContext
  // =================================================================
protected:
  virtual void OnStart(const ActivityOption& option) override;
  virtual void OnEnd() override;

};