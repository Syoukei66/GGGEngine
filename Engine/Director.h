#pragma once

#include <Engine/Scene/SceneManager.h>
#include <Engine/Scene/Scene.h>

#include <Engine/Engine/Engine.h>

class Director
{
  friend class Engine;
  
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(Director);

  // =================================================================
  // Methods
  // =================================================================
public:
  static GG_INLINE void PushScene(const SharedRef<Scene>& next)
  {
    Self().engine_->GetSceneManager()->PushScene(next);
  }
  static GG_INLINE void PopScene()
  {
    Self().engine_->GetSceneManager()->PopScene();
  }
  static GG_INLINE void ChangeScene(const SharedRef<Scene>& next)
  {
    Self().engine_->GetSceneManager()->ChangeScene(next);
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  static GG_INLINE SharedRef<Scene> GetNowScene()
  {
    return Self().engine_->GetSceneManager()->GetNowScene();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Engine* engine_;

};
