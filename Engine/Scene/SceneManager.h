#pragma once

#include "Scene.h"

class SceneTransitioner;
class UpdateEventState;

class SceneManager
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  SceneManager();
  ~SceneManager();

  // =================================================================
  // Methods
  // =================================================================
public:
  void PushScene(const SharedRef<Scene>& next);
  void PopScene();
  void ChangeScene(const SharedRef<Scene>& next);

  void Update(const UpdateEventState& state);
  void Draw();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<Scene> GetNowScene()
  {
    return this->scene_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT32 second_elapsed_from_last_render_; //ƒ~ƒŠ•b‚È‚Ì‚Åint

  SharedRef<Scene> scene_;
  std::deque<SharedRef<Scene>> scene_stack_;
  SceneTransitioner* scene_transitioner_;
};
