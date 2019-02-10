#include "SceneManager.h"
#include "Scene.h"

// =================================================================
// Methods
// =================================================================
void SceneManager::PushScene(const SharedRef<Scene>& next)
{
  this->next_scene_ = next;
  this->scene_stack_.push_back(this->now_scene_);
}

void SceneManager::PopScene()
{
  this->next_scene_ = this->scene_stack_.back();
  this->scene_stack_.pop_back();
}

void SceneManager::ChangeScene(const SharedRef<Scene>& next)
{
  this->next_scene_ = next;
}

void SceneManager::ClearScene(const ActivityContext& context)
{
  for (const SharedRef<Scene>& scene : this->scene_stack_)
  {
    scene->Hide(context);
    scene->Unload(context);
  }
  this->scene_stack_.clear();
  if (this->now_scene_)
  {
    this->now_scene_->Hide(context);
    this->now_scene_->Unload(context);
    this->now_scene_ = nullptr;
  }
}

void SceneManager::Update(const ActivityContext& context)
{
  // �J�ڐ�̃V�[�����o�^����Ă�����A�J�ڏ������s��
  if (this->next_scene_)
  {
    // �A�����[�h�t���O���o���Ă���ΌÂ��V�[�����A�����[�h
    if (this->now_scene_)
    {
      this->now_scene_->Hide(context);
      this->now_scene_->Unload(context);
    }
    this->now_scene_ = this->next_scene_;
    if (this->now_scene_)
    {
      this->now_scene_->Load(context);
      this->now_scene_->Show(context);
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
