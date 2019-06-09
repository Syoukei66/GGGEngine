#include "GameObject.h"

#include <Engine/Component/Renderer/Renderer.h>

// =================================================================
// Constructor / Destructor
// =================================================================
GG_CREATE_FUNC_IMPL(GameObject)
{
  return GameObject::Init("GameObject");
}

GG_CREATE_FUNC_IMPL_1(GameObject, const std::string&, name)
{
  this->name_ = name;
  this->enabled_ = true;
  this->transform_ = new Transform(this);
  this->transform_->Init();
  return true;
}

GG_DESTRUCT_FUNC_IMPL(GameObject)
{
  delete this->transform_;
  return true;
}

// =================================================================
// Methods
// =================================================================
void GameObject::AddChild(const SharedRef<GameObject>& child)
{
  child->parent_ = this;
  this->children_.emplace_back(child);
  child->OnWorldTransformChanged();
}

void GameObject::RemoveSelf()
{
  if (!this->parent_)
  {
    return;
  }
  const auto& itr = std::find(this->parent_->children_.begin(), this->parent_->children_.end(), SharedRef<GameObject>(this));
  this->parent_->children_.erase(itr);
  this->parent_ = nullptr;
}

void GameObject::ClearChildren()
{
  this->children_.clear();
}

// =================================================================
// Events
// =================================================================
void GameObject::Draw(GameObjectRenderState* state)
{
  if (!this->enabled_)
  {
    return;
  }
  if (this->HasComponent<Renderer>())
  {
    this->GetComponent<Renderer>()->ReserveDraw(state);
  }

  // Žq‚Ì•`‰æ
  for (const SharedRef<GameObject>& child : this->children_)
  {
    child->Draw(state);
  }
}

void GameObject::ManagedPreUpdate()
{
  if (!this->enabled_)
  {
    return;
  }
  this->PreUpdate();
  for (const SharedRef<GameObject>& child : this->children_)
  {
    child->ManagedPreUpdate();
  }
}

void GameObject::ManagedUpdate()
{
  if (!this->enabled_)
  {
    return;
  }
  this->Update();
  for (const SharedRef<GameObject>& child : this->children_)
  {
    child->ManagedUpdate();
  }
}

void GameObject::ManagedPostUpdate()
{
  if (!this->enabled_)
  {
    return;
  }
  this->PostUpdate();
  for (const SharedRef<GameObject>& child : this->children_)
  {
    child->ManagedPostUpdate();
  }
}

void GameObject::OnWorldTransformChanged()
{
  this->transform_->OnWorldTransformDirty();
  for (const SharedRef<GameObject>& child : this->children_)
  {
    child->OnWorldTransformChanged();
  }
}
