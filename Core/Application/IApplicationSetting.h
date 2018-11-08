#pragma once

#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Activity/Activity.h>
#include <Core/Application/Application.h>

/*!
 * @brief Applicationの設定を行うクラス
 */
class IApplicationSetting
{
  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief MainActivityの作成やAPIの設定などを行う
   */
  virtual void SetupApplication(Application* app, const ActivityOption& ao, SharedRef<Activity>* activity, SharedRef<GraphicsAPI>* graphics, SharedRef<InputAPI>* input, SharedRef<AudioAPI>* audio) = 0;

};