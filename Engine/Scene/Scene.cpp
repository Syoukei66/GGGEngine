#include "Scene.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GG_INIT_FUNC_IMPL(Scene)
{
  this->is_loaded_ = false;
  this->root2d_ = new GameObject2D();
  this->root3d_ = new GameObject3D();
  return true;
}

GG_DESTRUCT_FUNC_IMPL(Scene)
{
  if (this->root2d_)
  {
    delete this->root2d_;
  }
  if (this->root3d_)
  {
    delete this->root3d_;
  }
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
  for (std::vector<Camera*>::iterator itr = this->cameras_.begin(); itr != this->cameras_.end(); ++itr)
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
