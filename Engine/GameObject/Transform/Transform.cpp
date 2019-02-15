#include "Transform.h"

#include <Engine/GameObject/GameObject.h>

// =================================================================
// Constructor / Destructor
// =================================================================
Transform::Transform(GameObject* entity)
  : entity_(entity)
  , translate_matrix_()
  , scale_matrix_()
  , matrix_()
  , world_matrix_()
  , translation_dirty_()
  , rotation_dirty_()
  , scale_dirty_()
  , world_transform_dirty_()
  , position_()
  , scale_()
  , scale_max_(1.0f)
  , rotator_(this)
{
}

// =================================================================
// Methods
// =================================================================
void Transform::Init()
{
  this->position_ = TVec3f(0.0f, 0.0f, 0.0f);
  this->scale_ = TVec3f(1.0f, 1.0f, 1.0f);
  this->rotator_.Init();
  this->OnTransformChanged();
  this->OnScaleChanged();
  this->OnRotationChanged();
  this->OnWorldTransformDirty();
}

void Transform::OnTransformChanged()
{
  this->translation_dirty_ = true;
  this->entity_->OnWorldTransformChanged();
}

void Transform::OnScaleChanged()
{
  this->scale_dirty_ = true;
  this->entity_->OnWorldTransformChanged();
}

void Transform::OnRotationChanged()
{
  this->rotation_dirty_ = true;
  this->entity_->OnWorldTransformChanged();
}

void Transform::OnWorldTransformDirty()
{
  this->world_transform_dirty_ = true;
}

void Transform::UpdateMatrix()
{
  //TODO: s—ñ‰‰ŽZ‚ð‚í‚´‚í‚´s‚í‚È‚¢‚æ‚¤‚É‚·‚ê‚Î‚‘¬‰»‚ª}‚ê‚é‚©‚à
  bool matrix_dirty = false;
  if (this->translation_dirty_)
  {
    this->translate_matrix_ = Matrix4x4::identity;
    this->translate_matrix_.Translation(this->position_);
    this->translation_dirty_ = false;
    matrix_dirty = true;
  }
  if (this->scale_dirty_)
  {
    this->scale_matrix_ = Matrix4x4::identity;
    this->scale_matrix_.Scaling(this->scale_);
    this->scale_dirty_ = false;
    matrix_dirty = true;
  }
  if (this->rotation_dirty_)
  {
    this->rotation_dirty_ = false;
    matrix_dirty = true;
  }
  if (matrix_dirty)
  {
    this->matrix_ = Matrix4x4::identity;
    this->matrix_ *= this->scale_matrix_;
    this->matrix_ *= this->rotator_.GetRotationMatrix();
    this->matrix_ *= this->translate_matrix_;
  }
}

void Transform::UpdateWorldMatrix()
{
  if (!this->world_transform_dirty_)
  {
    return;
  }
  this->world_matrix_ = this->GetMatrix();
  const SharedRef<GameObject>& parent = this->entity_->GetParent();
  if (parent)
  {
    this->world_matrix_ *= parent->GetTransform()->GetWorldMatrix();
  }
  this->world_transform_dirty_ = false;
}

// =================================================================
// Operation
// =================================================================
void Transform::Move(const TVec3f& value)
{
  this->SetPosition(this->GetPosition() + this->GetRotationMatrix() * value);
}

void Transform::Move(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  this->SetPosition(this->GetPosition() + this->GetRotationMatrix() * TVec3f(x, y, z));
}

void Transform::MoveX(T_FLOAT x)
{
  this->SetPosition(this->GetPosition() + this->GetRotationMatrix() * TVec3f(x, 0.0f, 0.0f));
}

void Transform::MoveY(T_FLOAT y)
{
  this->SetPosition(this->GetPosition() + this->GetRotationMatrix() * TVec3f(0.0f, y, 0.0f));
}

void Transform::MoveZ(T_FLOAT z)
{
  this->SetPosition(this->GetPosition() + this->GetRotationMatrix() * TVec3f(0.0f, 0.0f, z));
}

void Transform::LookAt(const TVec3f& target, const TVec3f& up)
{
  const TVec3f z = (target - this->GetWorldPosition()).Normalized();
  const TVec3f x = TVec3f::Cross(up, z);
  const TVec3f y = TVec3f::Cross(z, x);

  Matrix4x4 mat = Matrix4x4::identity;
  mat._11 = x.x; mat._21 = y.x; mat._31 = z.x;
  mat._12 = x.y; mat._22 = y.y; mat._32 = z.y;
  mat._13 = x.z; mat._23 = y.z; mat._33 = z.z;
  this->rotator_.FromRotationMatrix(mat);
}

// =================================================================
// Setter / Getter
// =================================================================
void Transform::SetPosition(const TVec3f& position)
{
  if (this->position_ == position)
  {
    return;
  }
  this->position_ = position;
  this->OnTransformChanged();
}

void Transform::SetPosition(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  if (
    this->position_.x == x &&
    this->position_.y == y &&
    this->position_.z == z
    )
  {
    return;
  }
  this->position_.x = x;
  this->position_.y = y;
  this->position_.z = z;
  this->OnTransformChanged();
}

void Transform::SetX(T_FLOAT x)
{
  if (this->position_.x == x)
  {
    return;
  }
  this->position_.x = x;
  this->OnTransformChanged();
}

void Transform::SetY(T_FLOAT y)
{
  if (this->position_.y == y)
  {
    return;
  }
  this->position_.y = y;
  this->OnTransformChanged();
}

void Transform::SetZ(T_FLOAT z)
{
  if (this->position_.z == z)
  {
    return;
  }
  this->position_.z = z;
  this->OnTransformChanged();
}

void Transform::SetScale(const TVec3f & scale)
{
  if (this->scale_ == scale)
  {
    return;
  }
  this->scale_ = scale;
  this->scale_max_ = std::max(scale.x, std::max(scale.y, std::max(scale.z, this->scale_max_)));
  this->OnScaleChanged();
}

void Transform::SetScale(T_FLOAT scale)
{
  if (
    this->scale_.x == scale &&
    this->scale_.y == scale &&
    this->scale_.z == scale
    )
  {
    return;
  }
  this->scale_.x = scale;
  this->scale_.y = scale;
  this->scale_.z = scale;
  this->scale_max_ = std::max(scale, this->scale_max_);
  this->OnScaleChanged();
}

void Transform::SetScale(T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z)
{
  if (
    this->scale_.x == scale_x &&
    this->scale_.y == scale_y &&
    this->scale_.z == scale_z
    )
  {
    return;
  }
  this->scale_.x = scale_x;
  this->scale_.y = scale_y;
  this->scale_.z = scale_z;
  this->scale_max_ = std::max(scale_x, std::max(scale_y, std::max(scale_z, this->scale_max_)));
  this->OnScaleChanged();
}

void Transform::SetScaleX(T_FLOAT scale_x)
{
  if (this->scale_.x == scale_x)
  {
    return;
  }
  this->scale_.x = scale_x;
  this->scale_max_ = std::max(scale_x, this->scale_max_);
  this->OnScaleChanged();
}

void Transform::SetScaleY(T_FLOAT scale_y)
{
  if (this->scale_.y == scale_y)
  {
    return;
  }
  this->scale_.y = scale_y;
  this->scale_max_ = std::max(scale_y, this->scale_max_);
  this->OnScaleChanged();
}

void Transform::SetScaleZ(T_FLOAT scale_z)
{
  if (this->scale_.z == scale_z)
  {
    return;
  }
  this->scale_.z = scale_z;
  this->scale_max_ = std::max(scale_z, this->scale_max_);
  this->OnScaleChanged();
}
