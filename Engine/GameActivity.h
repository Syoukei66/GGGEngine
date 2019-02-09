#pragma once

#include <Engine/Scene/SceneManager.h>

class GameActivity : public Activity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(GameActivity);
  GG_CREATE_FUNC(GameActivity) { return true; }

  // =================================================================
  // Methods from Activity
  // =================================================================
protected:
  virtual void OnStart() override;
  virtual void OnEnd() override;
  virtual void OnUpdate() override;
  virtual void OnDraw(const SharedRef<Platform>& platform);

  // =================================================================
  // Methods
  // =================================================================
public:
  GG_INLINE void PushScene(const SharedRef<Scene>& next)
  {
    this->scene_manager_->PushScene(next);
  }

  GG_INLINE void PopScene()
  {
    this->scene_manager_->PopScene();
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

};