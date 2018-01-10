#include "Scene.h"
#include <stdlib.h>
#include <math.h>

#include "Engine.h"
#include "Camera.h"
#include "ResourcePool.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Scene::Scene()
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
  this->OnLoad(&ResourcePool::GetInstance());
  ResourcePool::GetInstance().Realize(listener);
  this->OnSetup();
}

void Scene::Unload()
{
  this->OnUnload();
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
  for (std::vector<Camera*>::iterator itr = this->cameras_.begin(); itr != this->cameras_.end(); ++itr)
  {
    (*itr)->DrawScene(this);
  }
}

void Scene::Draw2DLayers(GameObject2DRenderState* state)
{
  this->root2d_->Draw(state);
}

void Scene::Draw3DLayers(GameObject3DRenderState* state)
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
