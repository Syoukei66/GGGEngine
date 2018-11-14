#include "SceneManager.h"
#include "Scene.h"

// =================================================================
// Methods
// =================================================================
void SceneManager::PushScene(const SharedRef<Scene>& next, bool load_current)
{
  if (this->now_scene_)
  {
    this->now_scene_->Hide();
    this->scene_stack_.push_back(this->now_scene_);
  }
  this->now_scene_ = next;
  if (load_current)
  {
    this->now_scene_->Load();
  }
  this->now_scene_->Show();
}

void SceneManager::PopScene(bool unload_current)
{
  this->now_scene_->Hide();
  if (unload_current)
  {
    this->now_scene_->Unload();
  }
  this->now_scene_ = this->scene_stack_.back();
  this->scene_stack_.pop_back();
  if (this->now_scene_)
  {
    this->now_scene_->Show();
  }
}

void SceneManager::ChangeScene(const SharedRef<Scene>& next)
{
  if (this->now_scene_)
  {
    this->now_scene_->Hide();
    this->now_scene_->Unload();
  }
  this->now_scene_ = next;
  this->now_scene_->Load();
  this->now_scene_->Show();
}

void SceneManager::ClearScene()
{
  for (const SharedRef<Scene>& scene : this->scene_stack_)
  {
    scene->Hide();
    scene->Unload();
  }
  this->scene_stack_.clear();
  if (this->now_scene_)
  {
    this->now_scene_->Hide();
    this->now_scene_->Unload();
    this->now_scene_ = nullptr;
  }
}

void SceneManager::Update(const UpdateEventState& state)
{
  if (!this->now_scene_)
  {
    return;
  }
  this->now_scene_->OnUpdateEvent();
}

void SceneManager::Draw()
{
  if (!this->now_scene_)
  {
    return;
  }
  this->now_scene_->Draw();
}
