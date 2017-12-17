#include "GameObject3D.h"
#include "GameObject3DRenderState.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObject3D::GameObject3D()
  : parent_(nullptr)
  , children_()
  , z_test_(false)
{
  this->SetBlendFunction(BlendFunction::BL_NOBLEND, BlendFunction::BL_NOBLEND);
  this->transform_ = new Transform3D(this);
  this->transform_->Init();
}

GameObject3D::~GameObject3D()
{
  if (this->transform_)
  {
    delete this->transform_;
  }
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

  this->transform_->UpdateWorldMatrix(NativeMethod::Matrix().Matrix4x4Stack_GetTop(state->GetMatrixStack()));

  if (state->IsTargetedLayer(this->GetLayerId()))
  {
    //TODO: Zテスト行うかどうかの判定はマテリアルに記述すべき
    if (this->z_test_)
    {
      state->AddZCheckOrder(this);
    }
    else
    {
      // 自分自身の描画
      this->NativeDraw(state);
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

void GameObject3D::ConvertPositionLocalToWorld(const TVec3f* local, TVec3f* dest, GameObject3D* root) const
{
  if (local)
  {
    (*dest) += (*local);
  }
  this->transform_->ApplyMatrixToPosition(dest);
  //(*dest) += this->GetTransform()->GetMatrixAppliedPosition();
  if (!this->parent_ || this->parent_ == root)
  {
    return;
  }
  this->parent_->ConvertPositionLocalToWorld(nullptr, dest, root);

}

void GameObject3D::ConvertPositionLocalToWorld(T_FLOAT local_x, T_FLOAT local_y, T_FLOAT local_z, TVec3f* dest, GameObject3D* root) const
{
  this->ConvertPositionLocalToWorld(&TVec3f(local_x, local_y, local_z), dest, root);
}

T_FLOAT GameObject3D::ConvertXLocalToWorld(T_FLOAT local_x, GameObject3D* root) const
{
  return this->transform_->GetWorldPosition(root).x + local_x;
}

T_FLOAT GameObject3D::ConvertYLocalToWorld(T_FLOAT local_y, GameObject3D* root) const
{
  return this->transform_->GetWorldPosition(root).y + local_y;
}

T_FLOAT GameObject3D::ConvertZLocalToWorld(T_FLOAT local_z, GameObject3D* root) const
{
  return this->transform_->GetWorldPosition(root).z + local_z;
}

void GameObject3D::PushMatrixStack(GameObject3DRenderState* state)
{
  state->PushMatrix(this->transform_->GetMatrix());
}

void GameObject3D::PopMatrixStack(GameObject3DRenderState* state)
{
  state->PopMatrix();
}

// =================================================================
// Events
// =================================================================
void GameObject3D::FireOnPositionChanged(GameObject* root)
{
  this->transform_->OnWorldPositionDirty();
  this->OnPositionChanged(root);
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject3D* child = (*it);
    child->FireOnPositionChanged(root);
  }
}

void GameObject3D::FireOnScaleChanged(GameObject* root)
{
  this->transform_->OnWorldPositionDirty();
  this->OnScaleChanged(root);
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject3D* child = (*it);
    child->FireOnScaleChanged(root);
  }
}

void GameObject3D::FireOnRotationChanged(GameObject* root)
{
  this->transform_->OnWorldPositionDirty();
  this->OnRotationChanged(root);
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    GameObject3D* child = (*it);
    child->FireOnRotationChanged(root);
  }
}
