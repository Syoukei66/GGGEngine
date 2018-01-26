#include "GameObject3D.h"
#include "GameObject3DRenderState.h"
#include "NativeMethod.h"
#include "Camera3D.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObject3D::GameObject3D()
  : parent_(nullptr)
  , children_()
{
  this->transform_ = new Transform3D(this);
  this->transform_->Init();
}

GameObject3D::~GameObject3D()
{
  delete this->transform_;
}

// =================================================================
// Method
// =================================================================
void GameObject3D::Init()
{
  GameObject::Init();
}

void GameObject3D::ManagedPreUpdate()
{
  this->PreUpdate();
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    (*it)->ManagedPreUpdate();
  }
}

void GameObject3D::ManagedUpdate()
{
  this->Update();
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    (*it)->ManagedUpdate();
  }
}

void GameObject3D::ManagedPostUpdate()
{
  this->PostUpdate();
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    (*it)->ManagedPostUpdate();
  }
}

void GameObject3D::AddChild(GameObject3D* child)
{
  child->parent_ = this;
  this->children_.push_back(child);
  child->FireOnPositionChanged(this);
  child->FireOnScaleChanged(this);
  child->FireOnRotationChanged(this);
}

void GameObject3D::RemoveChild(GameObject3D* child)
{
  if (child->parent_ != this)
  {
    return;
  }
  child->parent_ = nullptr;
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    if (child == (*it))
    {
      this->children_.erase(it);
      return;
    }
  }
}

void GameObject3D::RemoveSelf()
{
  if (!this->parent_)
  {
    return;
  }
  this->parent_->RemoveChild(this);
}

void GameObject3D::ClearChildren()
{
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject3D* child = (*it);
    child->parent_ = nullptr;
  }
  this->children_.clear();
}

void GameObject3D::Draw(GameObject3DRenderState* state)
{ 
  if (!this->IsVisible())
  {
    return;
  }

  //描画前のアップデート処理
  this->PreDraw(state);

  this->PushMatrixStack(state);
  
  if (state->IsTargetedLayer(this->GetLayerId()))
  {
    Material* const material = this->GetMaterial();
    if (material && material->GetZTestLevel() > 0)
    {
      state->AddZCheckOrder(material->GetZTestLevel(), this);
    }
    else
    {
      // 自分自身の描画
      this->ManagedDraw(state);
    }
  }

  // 子の描画
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject3D* child = (*it);
    child->Draw(state);
  }

  this->PopMatrixStack(state);

  this->PostDraw(state);
}

void GameObject3D::ManagedDraw(GameObject3DRenderState* state)
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

void GameObject3D::PushMatrixStack(GameObject3DRenderState* state)
{
  state->PushMatrix(this->transform_->GetMatrix());
  //if (this->IsBillboardingRoot())
  //{
  //  state->PushMatrix(state->GetCamera()->GetBillboardingMatrix());
  //}
}

void GameObject3D::PopMatrixStack(GameObject3DRenderState* state)
{
  //if (this->IsBillboardingRoot())
  //{
  //  state->PopMatrix();
  //}
  state->PopMatrix();
}

// =================================================================
// Events
// =================================================================
void GameObject3D::FireOnPositionChanged(GameObject* root)
{
  this->transform_->OnWorldTransformDirty();
  this->OnPositionChanged(root);
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject3D* child = (*it);
    child->FireOnPositionChanged(root);
  }
}

void GameObject3D::FireOnScaleChanged(GameObject* root)
{
  this->transform_->OnWorldTransformDirty();
  this->OnScaleChanged(root);
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject3D* child = (*it);
    child->FireOnScaleChanged(root);
  }
}

void GameObject3D::FireOnRotationChanged(GameObject* root)
{
  this->transform_->OnWorldTransformDirty();
  this->OnRotationChanged(root);
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject3D* child = (*it);
    child->FireOnRotationChanged(root);
  }
}
