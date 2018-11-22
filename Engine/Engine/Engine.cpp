#include "Engine.h"

#include <Algorithm/EasingFunction/EasingFunctionManager.h>

#include <Engine/Component/Modifier/EntityModifierManager.h>
#include <Engine/GameObject/GameObject.h>
#include <Engine/Engine/EngineOption.h>
#include <Engine/Director.h>

// =================================================================
// Constructor / Destructor
// =================================================================
Engine::Engine(IEngineBehavior* engine_behavior)
  : engine_behavior_(engine_behavior)
  , scene_manager_()
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
  EngineOption eo;
  this->engine_behavior_->SetupEngineOption(eo);

  EntityModifierManager::Init(EntityModifierAllocateOption());
  EasingFunctionManager::Load(eo.easing_function_sampling_count_);

  this->engine_behavior_->OnGameBegin();

  Director::Self().engine_ = this;
  this->scene_manager_ = new SceneManager();
  this->scene_manager_->ChangeScene(this->engine_behavior_->FirstScene());
}

void Engine::Uninit()
{
  this->scene_manager_->ClearScene();
  delete this->scene_manager_;

  this->engine_behavior_->OnGameEnd();

  EasingFunctionManager::Unload();
  EntityModifierManager::Uninit();
}

void Engine::Update(const UpdateEventState& state)
{
  this->scene_manager_->Update(state);
}

void Engine::Draw()
{
  this->scene_manager_->Draw();
}
