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
private:
  static inline Director& GetInstance()
  {
    static Director self;
    return self;
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
  static inline void ChangeScene(Scene* next)
  {
    GetInstance().engine_->ChangeScene(next);
  }

  // =================================================================
  // setter/getter
  // =================================================================
public:
  static inline void SetNowScene(Scene* scene)
  {
    GetInstance().now_scene_ = scene;
  }

  static inline void SetActivity(BaseActivity* activity)
  {
    GetInstance().activity_ = activity;
  }

  static inline void SetEngine(Engine* engine)
  {
    GetInstance().engine_ = engine;
  }

  static inline const EngineOption* GetEngineOption()
  {
    return GetInstance().engine_->GetEngineOption();
  }

  static inline LP_DEVICE GetDevice()
  {
    return GetInstance().activity_->GetDevice();
  }

  static inline T_UINT8 GetFrameRate()
  {
    //TODO: ‰Â•Ï‚É‚µ‚½‚¢
    return 60;
  }

  static inline Scene* GetNowScene()
  {
    return GetInstance().engine_->GetNowScene();
  }

  static inline const TSize& GetScreenSize() 
  {
    return GetInstance().engine_->GetScreenSize();
  }

  static inline T_UINT16 GetScreenWidth()
  {
    return GetInstance().engine_->GetScreenWidth();
  }

  static inline T_UINT16 GetScreenHeight() 
  {
    return GetInstance().engine_->GetScreenHeight();
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
