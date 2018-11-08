#pragma once

#include <Core/Application/IApplicationSetting.h>

#include <Native/Windows/Activity/EditorWindowActivity.h>
#include <Native/Windows/API/Audio/XAudio/XAudioAPI.h>
#include <Native/Windows/API/Input/DirectInput/DirectInputAPI.h>

/*!
 * @brief エディタ専用のプラットフォーム設定
 */
class WindowsApplicationSetting_Editor : public IApplicationSetting
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  WindowsApplicationSetting_Editor(HWND hwnd)
    : window_handle_(hwnd)
  {
  }

  // =================================================================
  // Methods from ApplicationSetting
  // =================================================================
public:
  virtual void SetupApplication(Application* app, const ActivityOption& ao, SharedRef<Activity>* activity, SharedRef<GraphicsAPI>* graphics, SharedRef<InputAPI>* input, SharedRef<AudioAPI>* audio) override
  {
    (*activity) = EditorWindowActivity::Create(ao, this->window_handle_);
    (*input) = DirectInputAPI::Create(app->GetOption().input_setting);
    (*audio) = XAudioAPI::Create();
#if GG_GRAPHICS_API_DX9
    (*graphics) = DX9GraphicsAPI::Create();
#endif
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  HWND window_handle_;

};