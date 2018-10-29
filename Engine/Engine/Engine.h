#pragma once

#include <Core/NativeType.h>
#include <Core/Geometry.h>
#include "EngineOption.h"
#include "EngineInput.h"
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
  bool EndScene();
  bool End();

  void ChangeScene(Scene* next);

  //second_elapsed‚Ì’PˆÊ‚Íƒ~ƒŠ•b
  void OnUpdate();

  bool DrawWait();
  void OnDraw();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE Scene* GetNowScene()
  {
    return this->scene_;
  }
  GG_INLINE const TSizei& GetScreenSize() const
  {
    return this->option_->window_size;
  }
  GG_INLINE T_UINT16 GetScreenWidth() const
  {
    return this->option_->window_size.width;
  }
  GG_INLINE T_UINT16 GetScreenHeight() const
  {
    return this->option_->window_size.height;
  }
  GG_INLINE const EngineOption* GetEngineOption() const
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
