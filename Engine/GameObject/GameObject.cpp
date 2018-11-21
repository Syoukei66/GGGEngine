#include "GameObject.h"
#include <stdlib.h>

// =================================================================
// Constructor / Destructor
// =================================================================
GG_INIT_FUNC_IMPL(GameObject)
{
  this->enabled_ = true;
  return true;
}

GG_DESTRUCT_FUNC_IMPL(GameObject)
{
  delete this->renderer_;
  return true;
}

// =================================================================
// Methods
// =================================================================
void GameObject::AddChild(const SharedRef<GameObject>& child)
{
  child->parent_ = SharedRef<GameObject>(this);
  this->children_.emplace_back(child);
  child->FireOnPositionChanged();
  child->FireOnScaleChanged();
  child->FireOnRotationChanged();
}

void GameObject::RemoveSelf()
{
  if (!this->parent_)
  {
    return;
  }
  const auto& itr = std::find(this->parent_->children_.begin(), this->parent_->children_.end(), SharedRef<GameObject>(this));
  this->parent_->children_.erase(itr);
  this->parent_.Reset();
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
  if (this->renderer_)
  {
    this->renderer_->ReserveDraw(state);
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

void GameObject::FireOnPositionChanged()
{
  this->transform_->OnWorldTransformDirty();
  for (const SharedRef<GameObject>& child : this->children_)
  {
    child->FireOnPositionChanged();
  }
}

void GameObject::FireOnScaleChanged()
{
  this->transform_->OnWorldTransformDirty();
  for (const SharedRef<GameObject>& child : this->children_)
  {
    child->FireOnScaleChanged();
  }
}

void GameObject::FireOnRotationChanged()
{
  this->transform_->OnWorldTransformDirty();
  for (const SharedRef<GameObject>& child : this->children_)
  {
    child->FireOnRotationChanged();
  }
}
