#include "EngineBehavior.h"
#include "Scene/StencilShadowTestScene.h"

// =================================================================
// Methods from IEngineBehavior
// =================================================================
void EngineBehavior::SetupApplicationOption(ApplicationOption& option)
{
  option.input_setting.player_count_ = 4;
  for (T_UINT32 i = 0; i < GameInput::GAME_INPUT_DATANUM; ++i)
  {
    option.input_setting.entities_.push_back(GameInput::GetInputEntities()[i]);
  }
}

void EngineBehavior::SetupMainActivityOption(ActivityOption& option)
{
  option.window_size = TVec2f(1280, 720);
}

void EngineBehavior::SetupEngineOption(EngineOption& option)
{
}

Scene* EngineBehavior::FirstScene()
{
  return new StencilShadowTestScene();
}
