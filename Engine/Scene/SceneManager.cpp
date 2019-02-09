#include "SceneManager.h"
#include "Scene.h"

// =================================================================
// Methods
// =================================================================
void SceneManager::PushScene(const SharedRef<Scene>& next)
{
  if (this->now_scene_)
  {
    this->now_scene_->Hide();
    this->scene_stack_.push_back(this->now_scene_);
  }
  this->now_scene_ = next;
  this->now_scene_->Load();
  this->now_scene_->Show();
}

void SceneManager::PopScene()
{
  this->now_scene_->Hide();
  this->now_scene_->Unload();
  this->now_scene_ = this->scene_stack_.back();
  this->scene_stack_.pop_back();
  if (this->now_scene_)
  {
    this->now_scene_->Show();
  }
}

void SceneManager::ChangeScene(const SharedRef<Scene>& next)
{
  this->next_scene_ = next;
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

void SceneManager::Update(const ActivityContext& context)
{
  // 遷移先のシーンが登録されていたら、遷移処理を行う
  if (this->next_scene_)
  {
    // アンロードフラグが経っていれば古いシーンをアンロード
    if (this->now_scene_)
    {
      this->now_scene_->Hide();
      this->now_scene_->Unload();
    }
    this->now_scene_ = this->next_scene_;
    if (this->now_scene_)
    {
      this->now_scene_->Load();
      this->now_scene_->Show();
    }
    this->next_scene_ = nullptr;
  }
  if (!this->now_scene_)
  {
    return;
  }
  this->now_scene_->OnUpdateEvent(context);
}

void SceneManager::Draw(const ActivityContext& context)
{
  if (!this->now_scene_)
  {
    return;
  }
  this->now_scene_->Draw(context);
}
