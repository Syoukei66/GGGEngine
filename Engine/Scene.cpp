#include "Scene.h"

#include "Engine.h"
#include "UserResourcePool.h"
#include "GameObject2D.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Scene::Scene()
  : is_loaded_(false)
{
  //Root用のゲームオブジェクトを用意する必要があるかもしれない
  this->root_ = new GameObject2D();
}

Scene::~Scene()
{
  if (this->root_)
  {
    delete this->root_;
  }
}

// =================================================================
// Method
// =================================================================
void Scene::AddChild(GameObject* child)
{
  this->root_->AddChild(child);
}

void Scene::RemoveChild(GameObject* child)
{
  this->root_->RemoveChild(child);
}

void Scene::ClearChildren()
{
  this->root_->ClearChildren();
}

// =================================================================
// Event
// =================================================================
void Scene::Load(IResourceLoadingListener* listener)
{
  if (this->is_loaded_)
  {
    return;
  }
  this->OnLoad(&UserResourcePool::GetInstance());
  UserResourcePool::GetInstance().PreRealize(listener);
  UserResourcePool::GetInstance().Realize(listener);
  this->OnSetup();
  this->is_loaded_ = true;
}

void Scene::Unload()
{
  if (!this->is_loaded_)
  {
    return;
  }
  this->OnUnload();
  this->is_loaded_ = false;
}

void Scene::Show(ISceneShowListener* listener)
{
  this->OnShow(listener);
  if (!listener->IsShowFinishControlled())
  {
    listener->OnShowFinish();
  }
}

void Scene::ShowFinish()
{
  this->OnShowFinish();
}

void Scene::Hide(ISceneHideListener* listener)
{
  this->OnHide(listener);
  if (!listener->IsHideFinishControlled())
  {
    listener->OnHideFinish();
  }
}

void Scene::HideFinish()
{
  this->OnHideFinish();
}

void Scene::OnUpdateEvent()
{
  this->PreUpdate();
  this->root_->ManagedPreUpdate();

  this->Update();
  this->root_->ManagedUpdate();

  this->PostUpdate();
  this->root_->ManagedPostUpdate();
}

void Scene::Draw()
{
  this->camera_manager_->Draw();
  this->renderer_manager_->Draw();
}
