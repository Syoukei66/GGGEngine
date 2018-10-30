#include "Engine.h"
#include <Algorithm/EasingFunction/EasingFunctionManager.h>
#include <Engine/Component/Modifier/EntityModifierManager.h>
#include <Engine/Event/UpdateEventState.h>

// =================================================================
// Constructor / Destructor
// =================================================================
Engine::Engine()
  : second_elapsed_from_last_render_(0)
  , option_(nullptr)
  , scene_(nullptr)
  , scene_transitioner_(nullptr)
{}

Engine::~Engine()
{
}

// =================================================================
// Method
// =================================================================
bool Engine::Init(IEngineSetting* setting)
{
  this->option_ = new EngineOption();
  setting->SetupEngineOption(this->option_);

  EntityModifierManager::Init(EntityModifierAllocateOption());
  EasingFunctionManager::Load(this->option_->render_cycle);

  this->scene_transitioner_ = new SceneTransitioner();
  return true;
}

bool Engine::EndScene()
{
  delete this->scene_transitioner_;
  return true;
}

bool Engine::End()
{
  EasingFunctionManager::Unload();
  EntityModifierManager::Uninit();

  delete this->option_;
  return true;
}

void Engine::ChangeScene(Scene* next)
{
  this->scene_transitioner_->SetNextScene(next);
}

void Engine::OnUpdate()
{
  if (this->scene_transitioner_->IsDuringTransition())
  {
    this->scene_ = this->scene_transitioner_->Transition();
  }
  LP_DEVICE render_object = Director::GetDevice();
  Scene* now_scene = this->GetNowScene();
  if (!now_scene)
  {
    return;
  }
  //EntityModifierManager::GetInstance().OnUpdate(UpdateEventState::Self().GetDeltaTime());
  EntityModifierManager::OnUpdate(1);
  now_scene->OnInputEvent();
  now_scene->OnUpdateEvent();
}

bool Engine::DrawWait()
{
  const T_UINT16 render_cycle = this->option_->render_cycle;
  this->second_elapsed_from_last_render_ += UpdateEventState::GetDeltaTime();
  if (render_cycle <= 0 || render_cycle > this->second_elapsed_from_last_render_)
  {
    return false;
  }
  return true;
}

void Engine::OnDraw()
{
  Scene* now_scene = this->GetNowScene();
  if (!now_scene)
  {
    return;
  }
  now_scene->Draw();
  this->second_elapsed_from_last_render_ %= this->option_->render_cycle;
}
