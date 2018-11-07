#pragma once

#include <Core/Application/Activity/ActivityOption.h>

class GraphicsAPI;
class AudioAPI;
class InputAPI;
class Activity;

/*!
 * @brief ゲームのエントリポイントから呼び出される処理を定義するクラス
 */

class IPlatformSetting
{
  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief アクティビティの作成
   */
  virtual UniqueRef<Activity> CreateActivity(const ActivityOption& option) const = 0;

  /*!
   * @brief グラフィックスAPIの作成
   */
  virtual UniqueRef<GraphicsAPI> CreateGraphicsAPI() const = 0;

  /*!
   * @brief オーディオAPIの作成
   */
  virtual UniqueRef<AudioAPI> CreateAudioAPI() const = 0;

  /*!
   * @brief ハードウェア入力APIの作成
   */
  virtual UniqueRef<InputAPI> CreateInputAPI(const InputSetting& setting) const = 0;

};