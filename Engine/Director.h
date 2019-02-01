#pragma once

#include <Engine/Scene/SceneManager.h>
#include <Engine/Scene/Scene.h>
#include "GameActivity.h"

class Director
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(Director);

  // =================================================================
  // Methods
  // =================================================================
public:
  static GG_INLINE void PushScene(const SharedRef<Scene>& next, bool load = true)
  {
    SharedRef<GameActivity>::StaticCast(Application::GetMainActivity())->PushScene(next, load);
  }
  static GG_INLINE void PopScene(bool unload = true)
  {
    SharedRef<GameActivity>::StaticCast(Application::GetMainActivity())->PopScene(unload);
  }
  static GG_INLINE void ChangeScene(const SharedRef<Scene>& next)
  {
    SharedRef<GameActivity>::StaticCast(Application::GetMainActivity())->ChangeScene(next);
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  static GG_INLINE SharedRef<Scene> GetNowScene()
  {
    return SharedRef<GameActivity>::StaticCast(Application::GetMainActivity())->GetNowScene();
  }

};