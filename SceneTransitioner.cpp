#include "SceneTransitioner.h"

#include "Scene.h"
#include "Director.h"
#include "ResourceManager.h"

SceneTransitioner::SceneTransitioner()
  : now_scene_(nullptr)
  , next_scene_(nullptr)
  , state_(SCENE_TRANSITION_NONE)
{
}

Scene* SceneTransitioner::Transition()
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
  this->state_ = SCENE_TRANSITION_NONE;
}

void SceneTransitioner::OnHideFinish()
{
  if (this->now_scene_)
  {
    this->now_scene_->Unload();
    delete this->now_scene_;
  }
  this->now_scene_ = this->next_scene_;
  this->next_scene_ = nullptr;
  Director::GetInstance()->SetNowScene(this->now_scene_);
  if (this->now_scene_)
  {
    //TODO:���[�f�B���O�V�[���Ȃǂ�n��
    IResourceLoadingListener listener = IResourceLoadingListener();
    this->state_ = SCENE_TRANSITION_LOADING;
    this->now_scene_->Load(&listener);
    this->state_ = SCENE_TRANSITION_ON_SHOW;
    return;
  }
  this->OnShowFinish();
}

void SceneTransitioner::SetNextScene(Scene* scene)
{
  this->state_ = SCENE_TRANSITION_ON_HIDE;
  this->next_scene_ = scene;
}
