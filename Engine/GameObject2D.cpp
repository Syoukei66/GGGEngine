#include "GameObject2D.h"
#include "GameObjectRenderState.h"
#include "EntityModifier.h"
#include "EntityModifierManager.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObject2D::GameObject2D()
  : parent_(nullptr)
  , children_()
  , zindex_(0)
  , children_zindex_dirty_(false)
{
  this->transform_ = new Transform2D(this);
  this->transform_->Init();
}

GameObject2D::~GameObject2D()
{
  delete this->transform_;
}

// =================================================================
// Method
// =================================================================
void GameObject2D::Init()
{
  GameObject::Init();
  this->zindex_ = 0;
  this->children_zindex_dirty_ = true;
}

void GameObject2D::AddChild(GameObject2D* child)
{
  child->parent_ = this;
  this->children_.emplace_back(child);
  this->OnChildrenZIndexChanged();
  child->FireOnPositionChanged();
  child->FireOnScaleChanged();
  child->FireOnRotationChanged();
}

void GameObject2D::RemoveChild(GameObject2D* child)
{
  if (child->parent_ != this)
  {
    return;
  }
  child->parent_ = nullptr;
  for (std::vector<GameObject2D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    if (child == (*it))
    {
      this->children_.erase(it);
      return;
    }
  }
}

void GameObject2D::RemoveSelf()
{
  if (!this->parent_)
  {
    return;
  }
  this->parent_->RemoveChild(this);
}

void GameObject2D::ClearChildren()
{
  for (GameObject2D* child : this->children_)
  {
    child->parent_ = nullptr;
  }
  this->children_.clear();
}

void GameObject2D::RegisterEntityModifier(EntityModifierRoot* root)
{
  root->OnAttached(this);
}

void GameObject2D::UnregisterEntityModifier(EntityModifierRoot* root)
{
  if (root->GetTargetEntity() != this)
  {
    return;
  }
  root->OnDetached();
}

void GameObject2D::ClearEntityModifiers()
{
  EntityModifierManager::GetInstance().ClearModifiersWithTargetEntity(this);
}

// =================================================================
// Events
// =================================================================
void GameObject2D::ManagedPreUpdate()
{
  this->PreUpdate();
  for (GameObject2D* child : this->children_)
  {
    child->ManagedPreUpdate();
  }
}

void GameObject2D::ManagedUpdate()
{
  this->Update();
  for (GameObject2D* child : this->children_)
  {
    child->ManagedUpdate();
  }
}

void GameObject2D::ManagedPostUpdate()
{
  this->PostUpdate();
  for (GameObject2D* child : this->children_)
  {
    child->ManagedPostUpdate();
  }
}

void GameObject2D::FireOnPositionChanged()
{
  this->transform_->OnWorldTransformDirty();
  this->OnPositionChanged();
  for (GameObject2D* child : this->children_)
  {
    child->FireOnPositionChanged();
  }
}

void GameObject2D::FireOnScaleChanged()
{
  this->transform_->OnWorldTransformDirty();
  this->OnScaleChanged();
  for (GameObject2D* child : this->children_)
  {
    child->FireOnScaleChanged();
  }
}

void GameObject2D::FireOnRotationChanged()
{
  this->transform_->OnWorldTransformDirty();
  this->OnRotationChanged();
  for (GameObject2D* child : this->children_)
  {
    child->FireOnRotationChanged();
  }
}

void GameObject2D::OnChildrenZIndexChanged()
{
  this->children_zindex_dirty_ = true;
}

void GameObject2D::UpdateChildrenZIndex()
{
  if (!this->children_zindex_dirty_)
  {
    return;
  }
  std::sort(this->children_.begin(), this->children_.end(), [](GameObject2D* a, GameObject2D* b){ return a->zindex_ < b->zindex_; });
  this->children_zindex_dirty_ = false;
}

void GameObject2D::Draw(GameObjectRenderState* state)
{
  if (!this->IsVisible())
  {
    return;
  }

  //描画前のアップデート処理
  this->UpdateChildrenZIndex();

  // 1.zIndexが0未満の子GameObject
  // 2.自分自身
  // 3.zIndexが0以上の子GameObject
  //という順序で描画を行う
  bool self_already_drawed = false;
  for (GameObject2D* child : this->children_)
  {
    if (child->zindex_ == 0 && !self_already_drawed)
    {
      //2.自分自身
      this->ManagedDraw(state);
      self_already_drawed = true;
    }
    child->Draw(state);
  }
  if (!self_already_drawed)
  {
    //2.自分自身
    this->ManagedDraw(state);
  }
}