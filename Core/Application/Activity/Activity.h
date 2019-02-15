#pragma once

#include <Core/Application/Activity/ActivityOption.h>
#include <Core/Application/Event/UpdateEventState.h>
#include <Core/Application/Platform/Platform.h>
#include "ActivityContext.h"

/*!
 * @brief ウィンドウなど、１つのアプリケーション実行インスタンスのクラス
 */
class Activity : public GGObject
{
  friend class Application;

  // =================================================================
  // Methods
  // =================================================================
private:
  /*!
   * @brief アクティビティ初期化処理
   */
  void Start(const ActivityOption& ao, const InputSetting& setting, ActivityContext* context);

  /*!
   * @brief アクティビティ終了処理
   */
  void EndActivity();

  /*!
   * @brief コンテキスト終了処理
   */
  void EndContext();

  /*!
   * @brief アクティビティのアップデート処理
   * @return falseならアクティビティ終了
   */
  bool Update(const SharedRef<Platform>& platform);

protected:
  /*!
   * @brief 派生先で定義するアクティビティ初期化処理
   */
  virtual void OnStart() {}

  /*!
   * @brief 派生先で定義するアクティビティ終了処理
   */
  virtual void OnEnd() {}

  /*!
   * @brief 派生先で定義するアクティビティ更新処理
   */
  virtual void OnUpdate() {}

  /*!
   * @brief 派生先で定義するアクティビティ描画処理
   */
  virtual void OnDraw(const SharedRef<Platform>& platform) {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE ActivityContext& GetContext()
  {
    return *this->context_;
  }

  GG_INLINE const ActivityContext& GetContext() const
  {
    return *this->context_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  ActivityContext* context_;

};
