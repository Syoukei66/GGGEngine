#include "Scene.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GG_INIT_FUNC_IMPL(Scene)
{
  this->is_loaded_ = false;
  this->root2d_ = GameObject2D::Create("2d_root");
  this->root3d_ = GameObject3D::Create("3d_root");
  return true;
}

// =================================================================
// Methods
// =================================================================
void Scene::Load()
{
  if (this->is_loaded_)
  {
    return;
  }
  this->OnLoad();
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

void Scene::Show()
{
  this->OnShow();
}

void Scene::Hide()
{
  this->OnHide();
}

void Scene::Draw()
{
  for (const SharedRef<Camera>& camera : this->cameras_)
  {
    camera->DrawScene(this);
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
