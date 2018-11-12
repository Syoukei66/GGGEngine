#include "SceneTransitioner.h"

#include "Scene.h"

SceneTransitioner::SceneTransitioner()
  : now_scene_(nullptr)
  , next_scene_(nullptr)
  , state_(SCENE_TRANSITION_NONE)
{
}

SceneTransitioner::~SceneTransitioner()
{
  if (this->now_scene_)
  {
    this->now_scene_->Unload();
  }
  if (this->next_scene_)
  {
    this->next_scene_->Unload();
  }
}

SharedRef<Scene> SceneTransitioner::Transition()
{
  if (this->state_ == SCENE_TRANSITION_NONE)
  {
    return this->now_scene_;
  }

  if (this->state_ == SCENE_TRANSITION_ON_HIDE)
  {
    if (this->now_scene_)
    {
      this->state_ = SCENE_TRANSITION_HIDING;
      this->now_scene_->Hide(this);
    }
    else
    {
      this->OnHideFinish();
    }
    return this->now_scene_;
  }

  if (this->state_ == SCENE_TRANSITION_HIDING)
  {
    return this->now_scene_;
  }

  if (this->state_ == SCENE_TRANSITION_LOADING)
  {
    return nullptr;
  }

  if (this->state_ == SCENE_TRANSITION_ON_SHOW)
  {
    this->state_ = SCENE_TRANSITION_SHOWING;
    this->now_scene_->Show(this);
    return this->now_scene_;
  }

  if (this->state_ == SCENE_TRANSITION_SHOWING)
  {
    return this->now_scene_;
  }

  return nullptr;
}

void SceneTransitioner::OnShowFinish()
{
  if (this->now_scene_)
  {
    this->now_scene_->ShowFinish();
  }
  this->state_ = SCENE_TRANSITION_NONE;
}

void SceneTransitioner::OnHideFinish()
{
  if (this->now_scene_)
  {
    this->now_scene_->HideFinish();
    this->now_scene_->Unload();
  }
  this->now_scene_ = this->next_scene_;
  this->next_scene_ = nullptr;
  if (this->now_scene_)
  {
    this->state_ = SCENE_TRANSITION_LOADING;
    this->now_scene_->Load();
    this->state_ = SCENE_TRANSITION_ON_SHOW;
    return;
  }
  this->OnShowFinish();
}

void SceneTransitioner::SetNextScene(const SharedRef<Scene>& scene)
{
  if (this->now_scene_ == scene)
  {
    return;
  }
  this->state_ = SCENE_TRANSITION_ON_HIDE;
  this->next_scene_ = scene;
}
