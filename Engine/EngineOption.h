#pragma once

#include <Core/Geometry.h>
#include "Scene.h"
#include "EntityModifierManager.h"
#include "InputSetting.h"

struct EngineOption
{
  EngineOption()
    : window_size()
    , activity_name("Game")
    , render_cycle(1000 / 60)
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
  virtual void OnEngineInit() {}
  virtual void OnEngineFinal() {}

  virtual void OnGameInit() {}
  virtual void OnGameFinal() {}

  virtual void SetupEngineOption(EngineOption* option) {}

  virtual Scene* FirstScene() = 0;

};
