#include "Engine.h"
#include "Director.h"
#include "EasingFunctionManager.h"
#include "EntityModifierManager.h"
#include "ParticleDataManager.h"
#include "EngineResourcePool.h"
#include "UserResourcePool.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Engine::Engine()
  : second_elapsed_from_last_render_(0)
  , option_(nullptr)
  , scene_(nullptr)
  , scene_transitioner_()
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

  EngineResourcePool::GetInstance().Init();
  UserResourcePool::GetInstance().Init();
  EntityModifierManager::GetInstance().Init(&this->option_->entity_modifier_option);
  EasingFunctionManager::GetInstance()->Load(this->option_->render_cycle);
  return true;
}

bool Engine::End()
{
  EasingFunctionManager::GetInstance()->Unload();
  EntityModifierManager::GetInstance().Uninit();
  UserResourcePool::GetInstance().Uninit();
  EngineResourcePool::GetInstance().Uninit();
  delete this->option_;
  return true;
}

void Engine::ChangeScene(Scene* next)
{
  this->scene_transitioner_.SetNextScene(next);
}

void Engine::OnUpdate()
{
  if (this->scene_transitioner_.IsDuringTransition())
  {
    this->scene_ = this->scene_transitioner_.Transition();
  }
  LP_DEVICE render_object = Director::GetInstance()->GetDevice();
  Scene* now_scene = this->GetNowScene();
  if (!now_scene)
  {
    return;
  }
  now_scene->OnInputEvent();
  now_scene->OnUpdateEvent();
}

bool Engine::DrawWait()
{
  const T_UINT16 render_cycle = this->option_->render_cycle;
  this->second_elapsed_from_last_render_ += UpdateEventState::GetInstance()->GetDeltaTime();
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
