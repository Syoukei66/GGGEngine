#include "Scene.h"
#include <stdlib.h>
#include <math.h>

#include "Engine.h"
#include "Camera2D.h"
#include "Camera3D.h"
#include "NativeMethod.h"
#include "UserResourcePool.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Scene::Scene()
  : is_loaded_(false)
{
  this->root2d_ = new GameObject2D();
  this->root3d_ = new GameObject3D();
}

Scene::~Scene()
{
  if (this->root2d_)
  {
    delete this->root2d_;
  }
  if (this->root3d_)
  {
    delete this->root3d_;
  }
}

// =================================================================
// Method
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

void Scene::Draw()
{
  for (std::vector<Camera3D*>::iterator itr = this->camera3ds_.begin(); itr != this->camera3ds_.end(); ++itr)
  {
    (*itr)->DrawScene(this);
  }
  for (std::vector<Camera2D*>::iterator itr = this->camera2ds_.begin(); itr != this->camera2ds_.end(); ++itr)
  {
    (*itr)->DrawScene(this);
  }
}

void Scene::Draw2DLayers(GameObjectRenderState* state)
{
  this->root2d_->Draw(state);
}

void Scene::Draw3DLayers(GameObjectRenderState* state)
{
  this->root3d_->Draw(state);
}

void Scene::OnUpdateEvent()
{
  this->PreUpdate();
  this->root2d_->ManagedPreUpdate();
  this->root3d_->ManagedPreUpdate();

  this->Update();
  this->root2d_->ManagedUpdate();
  this->root3d_->ManagedUpdate();

  this->PostUpdate();
  this->root2d_->ManagedPostUpdate();
  this->root3d_->ManagedPostUpdate();
}
