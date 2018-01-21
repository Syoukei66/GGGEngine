#ifndef HAL_ENGINE_DIRECTOR_DIRECTOR_H_
#define HAL_ENGINE_DIRECTOR_DIRECTOR_H_

#include "Scene.h"
#include "Engine.h"
#include "BaseActivity.h"

class Director
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static inline Director* GetInstance()
  {
    static Director self;
    return &self;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  Director() {}

  // =================================================================
  // Method
  // =================================================================
public:
  inline void ChangeScene(Scene* next)
  {
    this->engine_->ChangeScene(next);
  }

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void SetNowScene(Scene* scene)
  {
    this->now_scene_ = scene;
  }

  inline void SetActivity(BaseActivity* activity)
  {
    this->activity_ = activity;
  }

  inline void SetEngine(Engine* engine)
  {
    this->engine_ = engine;
  }

  inline const EngineOption* GetEngineOption()
  {
    return this->engine_->GetEngineOption();
  }

  inline LP_DEVICE GetDevice() const
  {
    return this->activity_->GetDevice();
  }

  inline FbxManager* GetFbxManager() const
  {
    return this->activity_->GetFbxManager();
  }

  inline T_UINT8 GetFrameRate() const
  {
    //TODO: ‰Â•Ï‚É‚µ‚½‚¢
    return 60;
  }

  inline Scene* GetNowScene() const
  {
    return this->engine_->GetNowScene();
  }

  inline const TSize& GetScreenSize() const
  {
    return this->engine_->GetScreenSize();
  }

  inline T_UINT16 GetScreenWidth() const
  {
    return this->engine_->GetScreenWidth();
  }

  inline T_UINT16 GetScreenHeight() const
  {
    return this->engine_->GetScreenHeight();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Scene* now_scene_;
  Engine* engine_;
  BaseActivity* activity_;
};

#endif//HAL_ENGINE_DIRECTOR_DIRECTOR_H_
