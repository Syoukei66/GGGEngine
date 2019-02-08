#include "EngineBehavior.h"
#include <Scene/EntryScene.h>
#include <Director.h>

// =================================================================
// Methods from IEngineBehavior
// =================================================================
void EngineBehavior::OnApplicationBegin()
{
}

void EngineBehavior::OnApplicationEnd()
{
}

void EngineBehavior::OnGameBegin()
{
  AssetConverterDirector::Init();
  AssetConverterDirector::Fetch();
}

void EngineBehavior::OnGameEnd()
{
  AssetConverterDirector::Uninit();
}

void EngineBehavior::SetupApplicationOption(ApplicationOption& option)
{
  option.input_setting.enable_state_ = InputContext::ONLY_ON_FOCUS;
  option.input_setting.cursol_input_id_ = EngineInput::Analog::ID_SCREEN_0_XY;
  option.input_setting.player_count_ = 1;
  for (T_UINT32 i = 0; i < GameInput::GAME_INPUT_DATANUM; ++i)
  {
    option.input_setting.entities_.push_back(GameInput::GetInputEntities()[i]);
  }
}

void EngineBehavior::SetupMainActivityOption(ActivityOption& option)
{
  option.window_size = TVec2f(1024, 576);
}

void EngineBehavior::SetupEngineOption(EngineOption& option)
{
}

SharedRef<Scene> EngineBehavior::FirstScene()
{
  return EntryScene::Create(AssetConverterDirector::GetContext());
}
