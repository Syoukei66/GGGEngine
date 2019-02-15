#include "Engine.h"

#include <Algorithm/EasingFunction/EasingFunctionManager.h>

#include <Engine/Component/Modifier/EntityModifierManager.h>
#include <Engine/GameObject/GameObject.h>
#include <Engine/Engine/EngineOption.h>

#include <Engine/GameActivity.h>

// =================================================================
// Constructor / Destructor
// =================================================================
Engine::Engine(IEngineBehavior* engine_behavior)
  : engine_behavior_(engine_behavior)
{
}

// =================================================================
// Methods
// =================================================================
void Engine::SetupApplicationOption(ApplicationOption& option)
{
  this->engine_behavior_->SetupApplicationOption(option);
}

void Engine::SetupMainActivityOption(ActivityOption& option)
{
  this->engine_behavior_->SetupMainActivityOption(option);
}

void Engine::OnApplicationBegin()
{
  this->engine_behavior_->OnApplicationBegin();
}

void Engine::OnApplicationEnd()
{
  this->engine_behavior_->OnApplicationEnd();
}

void Engine::Init()
{
  this->engine_behavior_->OnGameBegin();

  EngineOption eo;
  this->engine_behavior_->SetupEngineOption(eo);

  EntityModifierManager::Init(EntityModifierAllocateOption());
  EasingFunctionManager::Load(eo.easing_function_sampling_count_);

  const SharedRef<GameActivity>& activity = SharedRef<GameActivity>::StaticCast(Application::GetMainActivity());
  activity->ChangeScene(this->engine_behavior_->FirstScene());
}

void Engine::Uninit()
{
  EasingFunctionManager::Unload();
  EntityModifierManager::Uninit();

  this->engine_behavior_->OnGameEnd();
}

SharedRef<Activity> Engine::CreateMainActivity()
{
  return GameActivity::Create();
}
