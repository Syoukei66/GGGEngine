#pragma once

class InputSettingBuilder;
class Scene;

struct EngineOption
{
  EngineOption()
    : window_size()
    , activity_name("Game")
    , render_cycle(1000 / 60)
    , input_setting()
  {}

  TVec2f window_size;
  const char* activity_name;
  T_UINT16 render_cycle;
  InputSettingBuilder input_setting;
};

class IEngineSetting
{
  // =================================================================
  // Method
  // =================================================================
public:
  virtual void OnEngineInit() {}
  virtual void OnEngineFinal() {}

  virtual void OnGameInit() {}
  virtual void OnGameFinal() {}

  virtual void SetupEngineOption(EngineOption* option) {}

  virtual Scene* FirstScene() = 0;

};
