#pragma once

struct EngineOption;

/*!
 * @brief エンジンの動作を定義するクラス
 */
class IEngineBehavior 
{
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
   * @brief エンジン設定のカスタマイズ
   */
  virtual void SetupEngineOption(EngineOption& option) = 0;

  /*!
   * @brief アプリケーション作成時に呼ばれるイベント
   */
  virtual void OnApplicationBegin() {}

  /*!
   * @brief アプリケーション終了時に呼ばれるイベント
   */
  virtual void OnApplicationEnd() {}

  /*!
   * @brief ゲーム開始時に呼ばれるイベント
   */
  virtual void OnGameBegin() {}

  /*!
   * @brief ゲーム開始時に呼ばれるイベント
   */
  virtual void OnGameEnd() {}

  /*!
   * @brief 最初に呼び出されるScene
   */
  virtual SharedRef<Scene> FirstScene() = 0;
};