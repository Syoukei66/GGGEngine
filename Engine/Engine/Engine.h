#pragma once

#include <Engine/Engine/EngineOption.h>

class IEngineSetting;
class Scene;
class SceneTransitioner;

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
  GG_INLINE const TVec2f& GetScreenSize() const
  {
    return this->option_->window_size;
  }
  GG_INLINE T_FLOAT GetScreenWidth() const
  {
    return this->option_->window_size.width;
  }
  GG_INLINE T_FLOAT GetScreenHeight() const
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
