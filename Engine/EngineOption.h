#ifndef HAL_ENGINE_ENGINE_ENGINEOPTION_H_
#define HAL_ENGINE_ENGINE_ENGINEOPTION_H_

#include "Geometry.h"
#include "Scene.h"
#include "TexturePaletteManager.h"
#include "EntityModifierManager.h"
#include "ParticleDataManager.h"
#include "SpineDataManager.h"
#include "InputSetting.h"

class AssetPath
{
public:
  AssetPath()
    : root("")
    , texture("")
    , particle("")
  {}

public:
  void GetTexturePath(const char* path, char* dest) const;
  void GetParticlePath(const char* path, char* dest) const;
  void GetSpinePath(const char* path, char* dest) const;

public:
  const char* root;
  const char* texture;
  const char* particle;
  const char* spine;
  
};

struct EngineOption
{
  EngineOption()
    : window_size()
    , activity_name("Game")
    , asset_path()
    , render_cycle(60)
    , entity_modifier_option()
    , input_setting()
  {}

  TSize window_size;
  const char* activity_name;
  AssetPath asset_path;
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
    this->SetupAssetPath(&option->asset_path);
    option->render_cycle = this->RenderCycle();
    this->InputSetting(&option->input_setting);
  }

  virtual void OnGameInit() = 0;
  virtual void OnGameFinal() = 0;

  virtual void InputSetting(InputSettingBuilder* setting) = 0;
  virtual Scene* FirstScene() = 0;
  virtual TSize WinodwSize() = 0;
  virtual const char* ActivityName() = 0;
  virtual void SetupAssetPath(AssetPath* path) = 0;
  virtual T_UINT16 RenderCycle() = 0;

  virtual void SetupTexturePalettes(TexturePaletteManager* manager) = 0;
  virtual void SetupParticleDatas(ParticleDataManager* manager) = 0;
  virtual void SetupSpineDatas(SpineDataManager* manager) = 0;

};

#endif//HAL_ENGINE_ENGINE_ENGINEOPTION_H_
