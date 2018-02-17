#ifndef HAL_ENGINE_ENGINE_ENGINEOPTION_H_
#define HAL_ENGINE_ENGINE_ENGINEOPTION_H_

#include "Geometry.h"
#include "Scene.h"
#include "EntityModifierManager.h"
#include "InputSetting.h"

struct EngineOption
{
  EngineOption()
    : window_size()
    , activity_name("Game")
    , render_cycle(60)
    , entity_modifier_option()
    , input_setting()
  {}

  TSize window_size;
  const char* activity_name;
  T_UINT16 render_cycle;
  EntityModifierAllocateOption entity_modifier_option;
  InputSettingBuilder input_setting;
};

class IEngineSetting
{
  // =================================================================
  // Method
  // =================================================================
public:
  void SetupEngineOption(EngineOption* option)
  {
    option->window_size = this->WinodwSize();
    option->activity_name = this->ActivityName();
    option->render_cycle = this->RenderCycle();
    this->InputSetting(&option->input_setting);
  }
  virtual void OnEngineInit() {};
  virtual void OnEngineFinal() {};

  virtual void OnGameInit() {};
  virtual void OnGameFinal() {};

  virtual void InputSetting(InputSettingBuilder* setting) = 0;
  virtual Scene* FirstScene() = 0;
  virtual TSize WinodwSize() = 0;
  virtual const char* ActivityName() = 0;
  virtual T_UINT16 RenderCycle() = 0;

};

#endif//HAL_ENGINE_ENGINE_ENGINEOPTION_H_
