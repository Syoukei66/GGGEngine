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
   */
  void PushScene(const SharedRef<Scene>& next);

  /*!
   * @brief 現在のSceneをSceneスタックに加えてSceneを切り替える
   */
  void PopScene();

  void ChangeScene(const SharedRef<Scene>& next);
  void ClearScene(const ActivityContext& context);

  void Update(const ActivityContext& context);
  void Draw(const ActivityContext& context);

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

  std::deque<SharedRef<Scene>> scene_stack_;
};
