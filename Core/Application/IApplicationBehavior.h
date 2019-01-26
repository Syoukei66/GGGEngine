#pragma once

#include <Core/Application/Activity/ActivityOption.h>
#include <Core/Application/ApplicationOption.h>
#include <Core/Application/Event/UpdateEventState.h>

class Scene;

/*!
 * @brief アプリケーションの動作を定義するクラス
 */
class IApplicationBehavior
{
  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief アプリケーション設定のカスタマイズ
   */
  virtual void SetupApplicationOption(ApplicationOption& option) = 0;

  /*!
   * @brief メインアクティビティ設定のカスタマイズ
   */
  virtual void SetupMainActivityOption(ActivityOption& option) = 0;

  /*!
   * @brief アプリケーション作成時に呼ばれるイベント
   */
  virtual void OnApplicationBegin() {}

  /*!
   * @brief アプリケーション終了時に呼ばれるイベント
   */
  virtual void OnApplicationEnd() {}

  /*!
   * @brief アプリケーションの開始処理
   */
  virtual void Init() = 0;

  /*!
   * @brief アプリケーションの終了処理
   */
  virtual void Uninit() = 0;

};
