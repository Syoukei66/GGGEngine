#pragma once

#include "Scene.h"

class UpdateEventState;

class SceneManager
{
  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief 現在のSceneをSceneスタックに加えてSceneを切り替える
   * Sceneのロード/アンロードは自動的に行われない
   */
  void PushScene(const SharedRef<Scene>& next, bool load_current = true);

  /*!
   * @brief 現在のSceneをSceneスタックに加えてSceneを切り替える
   * Sceneのロード/アンロードは自動的に行われない
   */
  void PopScene(bool unload_current = true);

  void ChangeScene(const SharedRef<Scene>& next, bool need_unload = true);
  void ClearScene();

  void Update();
  void Draw();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<Scene> GetNowScene()
  {
    return this->now_scene_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  SharedRef<Scene> now_scene_;

  /*!
   * @brief シーン遷移をアップデートのタイミングで行う為のバッファ
   */
  SharedRef<Scene> next_scene_;
  bool unload_now_scene_;

  std::deque<SharedRef<Scene>> scene_stack_;
};
