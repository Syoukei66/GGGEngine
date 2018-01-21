#include "GameObject2D.h"

#include <algorithm>
#include "EntityModifier.h"
#include "GameObject2DRenderState.h"
#include "Moniker.h"

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
  if (this->transform_)
  {
    delete this->transform_;
  }
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

void GameObject2D::ManagedPreUpdate()
{
  this->PreUpdate();
  for (std::vector<GameObject2D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    (*it)->ManagedPreUpdate();
  }
}

void GameObject2D::ManagedUpdate()
{
  this->Update();
  for (std::vector<GameObject2D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    (*it)->ManagedUpdate();
  }
}

void GameObject2D::ManagedPostUpdate()
{
  this->PostUpdate();
  for (std::vector<GameObject2D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    (*it)->ManagedPostUpdate();
  }
}

void GameObject2D::AddChild(GameObject2D* child)
{
  child->parent_ = this;
  this->children_.push_back(child);
  this->OnChildrenZIndexChanged();
  child->FireOnPositionChanged(this);
  child->FireOnScaleChanged(this);
  child->FireOnRotationChanged(this);
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
  for (std::vector<GameObject2D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject2D* child = (*it);
    child->parent_ = nullptr;
  }
  this->children_.clear();
}

void GameObject2D::Draw(GameObject2DRenderState* state)
{
  if (!this->IsVisible())
  {
    return;
  }

  //描画前のアップデート処理
  this->UpdateChildrenZIndex();

  this->PreDraw(state);

  this->PushMatrixStack(state);

  // 1.zIndexが0未満の子GameObject
  // 2.自分自身
  // 3.zIndexが0以上の子GameObject
  //という順序で描画を行う
  bool self_already_drawed = false;
  for (std::vector<GameObject2D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject2D* child = (*it);
    if (child->zindex_ == 0 && !self_already_drawed)
    {
      //2.自分自身
      if (state->IsTargetedLayer(this->GetLayerId()))
      {
        this->ManagedDraw(state);
      }
      self_already_drawed = true;
    }
    if (!child->IsVisible())
    {
      continue;
    }
    child->Draw(state);
  }
  if (!self_already_drawed)
  {
    //2.自分自身
    if (state->IsTargetedLayer(this->GetLayerId()))
    {
      this->ManagedDraw(state);
    }
  }

  this->PopMatrixStack(state);

  this->PostDraw(state);
}

void GameObject2D::ManagedDraw(GameObject2DRenderState* state)
{
  Material* const material = this->GetMaterial();
  if (!material)
  {
    return;
  }
  const T_UINT8 pass_count = material->Begin();
  for (T_UINT8 i = 0; i < pass_count; ++i)
  {
    material->BeginPass(i);
    material->SetWorldMatrix(state);
    material->CommitChanges();
    this->NativeDraw(state);
    material->EndPass();
  }
  material->End();
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
  HalEngine::Resource::GetEntityModifierManager()->ClearModifiersWithTargetEntity(this);
}

void GameObject2D::PushMatrixStack(GameObject2DRenderState* state)
{
  state->PushMatrix(this->transform_->GetMatrix());
}

void GameObject2D::PopMatrixStack(GameObject2DRenderState* state)
{
  state->PopMatrix();
}

// =================================================================
// Events
// =================================================================
void GameObject2D::FireOnPositionChanged(GameObject* root)
{
  this->transform_->OnWorldTransformDirty();
  this->OnPositionChanged(root);
  for (std::vector<GameObject2D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject2D* child = (*it);
    child->FireOnPositionChanged(root);
  }
}

void GameObject2D::FireOnScaleChanged(GameObject* root)
{
  this->transform_->OnWorldTransformDirty();
  this->OnScaleChanged(root);
  for (std::vector<GameObject2D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject2D* child = (*it);
    child->FireOnScaleChanged(root);
  }
}

void GameObject2D::FireOnRotationChanged(GameObject* root)
{
  this->transform_->OnWorldTransformDirty();
  this->OnRotationChanged(root);
  for (std::vector<GameObject2D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject2D* child = (*it);
    child->FireOnRotationChanged(root);
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
