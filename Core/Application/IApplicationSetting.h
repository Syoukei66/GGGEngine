#pragma once

#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Activity/Activity.h>
#include <Core/Application/Application.h>

/*!
 * @brief Application�̐ݒ���s���N���X
 */
class IApplicationSetting
{
  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief MainActivity�̍쐬��API�̐ݒ�Ȃǂ��s��
   */
  virtual void SetupApplication(Application* app, const ActivityOption& ao, SharedRef<Activity>* activity, SharedRef<GraphicsAPI>* graphics, SharedRef<InputAPI>* input, SharedRef<AudioAPI>* audio) = 0;

};