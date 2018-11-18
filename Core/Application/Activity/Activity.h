#pragma once

#include <Core/Application/Activity/ActivityOption.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
          
/*!
 * @brief アプリケーションを動作させるクラス
 */
class Activity : public GGObject
{
  friend class Application;

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_INIT_FUNC_1(Activity, const ActivityOption& option);

  // =================================================================
  // Methods
  // =================================================================
protected:
  /*!
   * @brief ゲームが続くかどうかの判定
   * @return falseならゲーム終了
   */
  virtual bool ContinueEnabled() = 0;

  /*!
   * @brief フレーム処理が有効かどうかの判定
   * @return falseならアップデート処理を行わず待機する
   */
  virtual bool FrameEnabled() = 0;

  /*!
   * @brief アクティビティがアクティブ状態か確かめる
   */
  virtual bool IsActive() = 0;

  /*!
   * @brief 描画処理が有効かどうかの判定
   * @param 経過時間(秒)
   * @return falseなら画面のアップデートを行わない
   */
  bool DrawEnabled(T_FLOAT delta_time);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE const ActivityOption& GetOption() const
  {
    return this->option_;
  }

  GG_INLINE const TVec2f& GetScreenSize()
  {
    return this->option_.window_size;
  }

  GG_INLINE T_FLOAT GetScreenWidth()
  {
    return this->option_.window_size.width;
  }

  GG_INLINE T_FLOAT GetScreenHeight()
  {
    return this->option_.window_size.height;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  ActivityOption option_;
  T_FLOAT elapsed_time_;

};
