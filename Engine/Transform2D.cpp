#include "Transform2D.h"
#include "GameObject2D.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Transform2D::Transform2D(GameObject2D* entity)
  : Transform(entity)
  , entity_(entity)
{}

Transform2D::~Transform2D()
{}

// =================================================================
// Method
// =================================================================
void Transform2D::OnInit()
{
  this->position_ = TVec2f(0.0f, 0.0f);
  this->scale_ = TVec2f(1.0f, 1.0f);
  this->rotation_ = 0.0f;

  this->world_position_ = TVec2f(0.0f, 0.0f);
  this->matrix_applied_position_ = TVec2f(0.0f, 0.0f);
}

void Transform2D::UpdateTranslateMatrix(LP_MATRIX_4x4 matrix)
{
  NativeMethod::Matrix().Matrix4x4_Translate(
    matrix,
    this->position_.x,
    this->position_.y,
    0.0f
  );
}

void Transform2D::UpdateScaleMatrix(LP_MATRIX_4x4 matrix)
{
  NativeMethod::Matrix().Matrix4x4_Scaling(
    matrix,
    this->scale_.x,
    this->scale_.y,
    1.0f
  );
}

void Transform2D::UpdateRotateMatrix(LP_MATRIX_4x4 matrix)
{
  NativeMethod::Matrix().Matrix4x4_Rotation(
    matrix,
    0.0f,
    0.0f,
    this->rotation_
  );
}

void Transform2D::OnUpdateMatrix(LP_MATRIX_4x4 matrix)
{
  this->matrix_applied_position_.x = 0.0f;
  this->matrix_applied_position_.y = 0.0f;
  NativeMethod::Matrix().Matrix4x4_Apply(
    matrix, 
    &this->matrix_applied_position_.x,
    &this->matrix_applied_position_.y,
    nullptr
  );
}

// =================================================================
// setter/getter
// =================================================================
TVec2f Transform2D::GetMatrixAppliedPosition()
{
  this->UpdateMatrix();
  return this->matrix_applied_position_;
}

void Transform2D::ApplyMatrixToPosition(TVec2f* dest)
{
  NativeMethod::Matrix().Matrix4x4_Apply(
    this->GetMatrix(),
    &(dest->x),
    &(dest->y),
    nullptr
  );
}

const TVec2f& Transform2D::GetWorldPosition(GameObject2D* root)
{
  if (this->world_position_dirty_)
  {
    this->world_position_.x = 0.0f;
    this->world_position_.y = 0.0f;
    this->entity_->ConvertPositionLocalToWorld(nullptr, &this->world_position_, root);
    this->world_position_dirty_ = false;
  }
  return this->world_position_;
}

T_FLOAT Transform2D::GetWorldX(GameObject2D* root)
{
  return this->GetWorldPosition(root).x;
}

T_FLOAT Transform2D::GetWorldY(GameObject2D* root)
{
  return this->GetWorldPosition(root).y;
}

void Transform2D::SetPositon(const TVec2f& position)
{
  if (this->position_ == position)
  {
    return;
  }
  this->position_ = position;
  this->OnTransformChanged();
}

void Transform2D::SetPositon(T_FLOAT x, T_FLOAT y)
{
  if (
    this->position_.x == x &&
    this->position_.y == y
    )
  {
    return;
  }
  this->position_.x = x;
  this->position_.y = y;
  this->OnTransformChanged();
}

void Transform2D::SetX(T_FLOAT x)
{
  if (this->position_.x == x)
  {
    return;
  }
  this->position_.x = x;
  this->OnTransformChanged();
}

void Transform2D::SetY(T_FLOAT y)
{
  if (this->position_.y == y)
  {
    return;
  }
  this->position_.y = y;
  this->OnTransformChanged();
}

void Transform2D::SetScale(const TVec2f& scale)
{
  if (this->scale_ == scale)
  {
    return;
  }
  this->scale_ = scale;
  this->OnScaleChanged();
}

void Transform2D::SetScale(T_FLOAT scale)
{
  if (
    this->scale_.x == scale &&
    this->scale_.y == scale
    )
  {
    return;
  }
  this->scale_.x = scale;
  this->scale_.y = scale;
  this->OnScaleChanged();
}

void Transform2D::SetScale(T_FLOAT scale_x, T_FLOAT scale_y)
{
  if (
    this->scale_.x == scale_x &&
    this->scale_.y == scale_y
    )
  {
    return;
  }
  this->scale_.x = scale_x;
  this->scale_.y = scale_y;
  this->OnScaleChanged();
}

void Transform2D::SetScaleX(T_FLOAT scale_x)
{
  if (this->scale_.x == scale_x)
  {
    return;
  }
  this->scale_.x = scale_x;
  this->OnScaleChanged();
}

void Transform2D::SetScaleY(T_FLOAT scale_y)
{
  if (this->scale_.y == scale_y)
  {
    return;
  }
  this->scale_.y = scale_y;
  this->OnScaleChanged();
}

void Transform2D::SetRotation(T_FLOAT rotation)
{
  if (this->rotation_ == rotation)
  {
    return;
  }
  this->rotation_ = rotation;
  this->OnRotationChanged();
}

