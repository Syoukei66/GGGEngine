#ifndef HAL_ENGINE_ENGINE_ENGINE_H_
#define HAL_ENGINE_ENGINE_ENGINE_H_

#include "NativeType.h"
#include "EngineOption.h"
#include "EngineInput.h"
#include "Geometry.h"
#include "Scene.h"

class Engine
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Engine();
  ~Engine();

  // =================================================================
  // Method
  // =================================================================
public:
  bool Init(IEngineSetting* setting);
  bool End();

  void ChangeScene(Scene* next);

  //second_elapsed‚Ì’PˆÊ‚Íƒ~ƒŠ•b
  void OnUpdate();

  bool DrawWait();
  void OnDraw();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline Scene* GetNowScene()
  {
    return this->scene_;
  }
  inline const TSize& GetScreenSize() const
  {
    return this->option_->window_size;
  }
  inline T_UINT16 GetScreenWidth() const
  {
    return this->option_->window_size.width;
  }
  inline T_UINT16 GetScreenHeight() const
  {
    return this->option_->window_size.height;
  }
  inline const EngineOption* GetEngineOption() const
  {
    return this->option_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT32 second_elapsed_from_last_render_; //ƒ~ƒŠ•b‚È‚Ì‚Åint
  EngineOption* option_;

  Scene* scene_;
  SceneTransitioner* scene_transitioner_;
};

#endif//HAL_ENGINE_ENGINE_ENGINE_H_
