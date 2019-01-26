#pragma once

#include <Core/Application/Activity/ActivityOption.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Event/UpdateEventState.h>
#include <Engine/Scene/SceneManager.h>

struct ImGuiContext;

/*!
 * @brief ウィンドウなど、１つのアプリケーション実行インスタンスのクラス
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
public:
  /*!
   * @brief アクティビティ初期化処理
   */
  void Start();

  /*!
   * @brief アクティビティ終了処理
   */
  void End();

  /*!
   * @brief アクティビティのアップデート処理
   * @return falseならアクティビティ終了
   */
  bool Update(const SharedRef<GraphicsAPI>& graphics_api, const SharedRef<InputAPI>& input_api);

protected:
  /*!
   * @brief プラットフォーム毎のアクティビティ初期化処理
   */
  virtual void OnStart() = 0;

  /*!
   * @brief プラットフォーム毎のアクティビティ終了処理
   */
  virtual void OnEnd() = 0;

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

  GG_INLINE void PushScene(const SharedRef<Scene>& next, bool load = true)
  {
    this->scene_manager_->PushScene(next, load);
  }

  GG_INLINE void PopScene(bool unload = true)
  {
    this->scene_manager_->PopScene(unload);
  }

  GG_INLINE void ChangeScene(const SharedRef<Scene>& next)
  {
    this->scene_manager_->ChangeScene(next);
  }

  GG_INLINE SharedRef<Scene> GetNowScene()
  {
    return this->scene_manager_->GetNowScene();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  SceneManager* scene_manager_;
  UpdateEventState update_event_state_;
  ActivityOption option_;
  T_FLOAT elapsed_time_;
  ImGuiContext* imgui_context_;

};
