#pragma once

#include <Core/Application/Platform/Platform.h>
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
   * @brief Platformを作成する
   * @return Platformのインスタンス
   */
  virtual UniqueRef<Platform> CreatePlatform(Application* app) const = 0;

};