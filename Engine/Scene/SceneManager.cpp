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

void SceneManager::ChangeScene(const SharedRef<Scene>& next, bool need_unload)
{
  this->next_scene_ = next;
  this->unload_now_scene_ = need_unload;
}

void SceneManager::ClearScene()
{
  std::set<SharedRef<Scene>> unloaded_scene = std::set<SharedRef<Scene>>();
  for (const SharedRef<Scene>& scene : this->scene_stack_)
  {
    if (unloaded_scene.find(scene) != unloaded_scene.end())
    {
      continue;
    }
    scene->Hide();
    scene->Unload();
    unloaded_scene.insert(scene);
  }
  this->scene_stack_.clear();
  if (this->now_scene_)
  {
    if (unloaded_scene.find(this->now_scene_) == unloaded_scene.end())
    {
      this->now_scene_->Hide();
      this->now_scene_->Unload();
      this->now_scene_ = nullptr;
    }
  }
}

void SceneManager::Update(const ActivityContext& context)
{
  // 遷移先のシーンが登録されていたら、遷移処理を行う
  if (this->next_scene_)
  {
    // アンロードフラグが経っていれば古いシーンをアンロード
    if (this->now_scene_ && this->unload_now_scene_)
    {
      this->now_scene_->Hide();
      this->now_scene_->Unload();
    }
    this->now_scene_ = this->next_scene_;
    this->now_scene_->Load();
    this->now_scene_->Show();
    this->next_scene_ = nullptr;
    this->unload_now_scene_ = false;
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
