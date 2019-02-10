#include "Scene.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GG_INIT_FUNC_IMPL(Scene)
{
  this->root_ = GameObject::Create("root");
  return true;
}

// =================================================================
// Methods
// =================================================================
void Scene::Load()
{
  if (this->load_count_ == 0)
  {
    this->OnLoad();
  }
  ++this->load_count_;
}

void Scene::Unload()
{
  --this->load_count_;
  if (this->load_count_ == 0)
  {
    this->OnUnload();
  }
}

void Scene::Show()
{
  if (this->is_shown_)
  {
    return;
  }
  this->OnShow();
  this->is_shown_ = true;
}

void Scene::Hide()
{
  if (!this->is_shown_)
  {
    return;
  }
  this->OnHide();
  this->is_shown_ = false;
}

void Scene::Draw(const ActivityContext& context)
{
  for (const SharedRef<Camera>& camera : this->cameras_)
  {
    camera->DrawScene(context, this);
  }
}

void Scene::DrawLayers(GameObjectRenderState* state)
{
  this->root_->Draw(state);
}

void Scene::OnUpdateEvent(const ActivityContext& context)
{
  this->PreUpdate(context);
  this->root_->ManagedPreUpdate();

  this->Update(context);
  this->root_->ManagedUpdate();

  this->PostUpdate(context);
  this->root_->ManagedPostUpdate();
}
