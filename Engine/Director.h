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
  static GG_INLINE void PushScene(const SharedRef<Scene>& next)
  {
    SharedRef<GameActivity>::StaticCast(Application::GetMainActivity())->PushScene(next);
  }
  static GG_INLINE void PopScene()
  {
    SharedRef<GameActivity>::StaticCast(Application::GetMainActivity())->PopScene();
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
  static GG_INLINE void SetIgnoreLog(bool ignore)
  {
    Self().ignore_log_ = ignore;
  }
  static GG_INLINE bool IsIgnoreLog()
  {
    return Self().ignore_log_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  bool ignore_log_;

};