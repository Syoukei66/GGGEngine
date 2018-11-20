#include "GameObject.h"
#include <stdlib.h>

// =================================================================
// Constructor / Destructor
// =================================================================
GameObject::GameObject()
  : enabled_(true)
  , parent_()
  , children_()
  , renderer_()
{
}

GameObject::~GameObject()
{
  delete this->renderer_;
}

// =================================================================
// Methods
// =================================================================
void GameObject::AddChild(GameObject* child)
{
  child->parent_ = this;
  this->children_.emplace_back(child);
  child->FireOnPositionChanged();
  child->FireOnScaleChanged();
  child->FireOnRotationChanged();
}

void GameObject::RemoveChild(GameObject* child)
{
  if (child->parent_ != this)
  {
    return;
  }
  child->parent_ = nullptr;
  for (std::vector<GameObject*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    if (child == (*it))
    {
      this->children_.erase(it);
      return;
    }
  }
}

void GameObject::RemoveSelf()
{
  if (!this->parent_)
  {
    return;
  }
  this->parent_->RemoveChild(this);
}

void GameObject::ClearChildren()
{
  for (GameObject* child : this->children_)
  {
    child->parent_ = nullptr;
  }
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
  for (GameObject* child : this->children_)
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
  for (GameObject* child : this->children_)
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
  for (GameObject* child : this->children_)
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
  for (GameObject* child : this->children_)
  {
    child->ManagedPostUpdate();
  }
}

void GameObject::FireOnPositionChanged()
{
  this->transform_->OnWorldTransformDirty();
  for (GameObject* child : this->children_)
  {
    child->FireOnPositionChanged();
  }
}

void GameObject::FireOnScaleChanged()
{
  this->transform_->OnWorldTransformDirty();
  for (GameObject* child : this->children_)
  {
    child->FireOnScaleChanged();
  }
}

void GameObject::FireOnRotationChanged()
{
  this->transform_->OnWorldTransformDirty();
  for (GameObject* child : this->children_)
  {
    child->FireOnRotationChanged();
  }
}
