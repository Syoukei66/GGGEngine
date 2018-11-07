#include "SceneManager.h"
#include "Scene.h"

// =================================================================
// Constructor / Destructor
// =================================================================
SceneManager::SceneManager()
  : second_elapsed_from_last_render_(0)
  , scene_(nullptr)
  , scene_transitioner_(nullptr)
{
  this->scene_transitioner_ = new SceneTransitioner();
}

SceneManager::~SceneManager()
{
  delete this->scene_transitioner_;
}

// =================================================================
// Methods
// =================================================================
void SceneManager::ChangeScene(Scene* next)
{
  this->scene_transitioner_->SetNextScene(next);
}

void SceneManager::Update(const UpdateEventState& state)
{
  if (this->scene_transitioner_->IsDuringTransition())
  {
    this->scene_ = this->scene_transitioner_->Transition();
  }
  Scene* now_scene = this->GetNowScene();
  if (!now_scene)
  {
    return;
  }
  now_scene->OnInputEvent();
  now_scene->OnUpdateEvent();
}

void SceneManager::Draw()
{
  Scene* now_scene = this->GetNowScene();
  if (!now_scene)
  {
    return;
  }
  now_scene->Draw();
}
