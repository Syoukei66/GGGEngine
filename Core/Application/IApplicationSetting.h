#pragma once

#include <Core/Application/Platform/Platform.h>
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
   * @brief Platform���쐬����
   * @return Platform�̃C���X�^���X
   */
  virtual UniqueRef<Platform> CreatePlatform(Application* app) const = 0;

};