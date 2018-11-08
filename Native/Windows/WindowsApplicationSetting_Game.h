#pragma once

#include <Core/Application/IApplicationSetting.h>

#include <Native/Windows/Activity/WindowActivity.h>
#include <Native/Windows/API/Audio/XAudio/XAudioAPI.h>
#include <Native/Windows/API/Input/DirectInput/DirectInputAPI.h>

/*!
 * @brief 通常のWindowsのプラットフォーム設定
 * ゲームではこちらを使用する
 */
class WindowsApplicationSetting_Game : public IApplicationSetting
{
  // =================================================================
  // Methods from ApplicationSetting
  // =================================================================
public:
  virtual void SetupApplication(Application* app, const ActivityOption& ao, SharedRef<Activity>* activity, SharedRef<GraphicsAPI>* graphics, SharedRef<InputAPI>* input, SharedRef<AudioAPI>* audio) override
  {
    (*activity) = WindowActivity::Create(ao);
    (*input) = DirectInputAPI::Create(app->GetOption().input_setting);
    (*audio) = XAudioAPI::Create();
#if GG_GRAPHICS_API_DX9
    (*graphics) = DX9GraphicsAPI::Create();
#endif
  }

};