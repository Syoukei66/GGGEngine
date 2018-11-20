#include "Transform3D.h"
#include <algorithm> 

#include <Engine/GameObject/GameObject3D.h>

#include "imgui\imgui.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Transform3D::Transform3D(GameObject3D* entity)
  : Transform(entity)
  , entity_(entity)
  , position_()
  , scale_()
  , scale_max_(1.0f)
{
  this->rotator_ = new Transform3DRotator(this);
}

Transform3D::~Transform3D()
{
  delete this->rotator_;
}

// =================================================================
// Methods
// =================================================================
void Transform3D::OnInit()
{
  this->position_ = TVec3f(0.0f, 0.0f, 0.0f);
  this->scale_ = TVec3f(1.0f, 1.0f, 1.0f);
  this->rotator_->Init();
}

void Transform3D::Move(const TVec3f& value)
{
  this->SetPosition(this->GetPosition() + this->GetRotationMatrix() * value);
}

void Transform3D::Move(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  this->SetPosition(this->GetPosition() + this->GetRotationMatrix() * TVec3f(x, y, z));
}

void Transform3D::MoveX(T_FLOAT x)
{
  this->SetPosition(this->GetPosition() + this->GetRotationMatrix() * TVec3f(x, 0.0f, 0.0f));
}

void Transform3D::MoveY(T_FLOAT y)
{
  this->SetPosition(this->GetPosition() + this->GetRotationMatrix() * TVec3f(0.0f, y, 0.0f));
}

void Transform3D::MoveZ(T_FLOAT z)
{
  this->SetPosition(this->GetPosition() + this->GetRotationMatrix() * TVec3f(0.0f, 0.0f, z));
}

void Transform3D::LookAt(const TVec3f& target, const TVec3f& up)
{
  const TVec3f z = (target - this->GetWorldPosition()).Normalized();
  const TVec3f x = TVec3f::Cross(up, z);
  const TVec3f y = TVec3f::Cross(z, x);

  Matrix4x4 mat = Matrix4x4::identity;
  mat._11 = x.x; mat._21 = y.x; mat._31 = z.x;
  mat._12 = x.y; mat._22 = y.y; mat._32 = z.y;
  mat._13 = x.z; mat._23 = y.z; mat._33 = z.z;
  this->rotator_->FromRotationMatrix(mat);
}

void Transform3D::UpdateTranslateMatrix(Matrix4x4* matrix)
{
  matrix->Translation(this->position_);
}

void Transform3D::UpdateScaleMatrix(Matrix4x4* matrix)
{
  matrix->Scaling(this->scale_);
}

void Transform3D::UpdateRotateMatrix(Matrix4x4* matrix)
{
  this->rotator_->ToRotationMatrix(matrix);
}

const Matrix4x4& Transform3D::GetParentWorldMatrix()
{
  GameObject3D* parent_ = (GameObject3D*)this->entity_->GetParent();
  if (!parent_)
  {
    return Matrix4x4::identity;
  }
  return parent_->GetTransform()->GetWorldMatrix();
}

// =================================================================
// Setter / Getter
// =================================================================
void Transform3D::SetPosition(const TVec3f& position)
{
  if (this->position_ == position)
  {
    return;
  }
  this->position_ = position;
  this->OnTransformChanged();
}

void Transform3D::SetPosition(T_FLOAT x, T_FLOAT y, T_FLOAT z)
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

void Transform3D::SetX(T_FLOAT x)
{
  if (this->position_.x == x)
  {
    return;
  }
  this->position_.x = x;
  this->OnTransformChanged();
}

void Transform3D::SetY(T_FLOAT y)
{
  if (this->position_.y == y)
  {
    return;
  }
  this->position_.y = y;
  this->OnTransformChanged();
}

void Transform3D::SetZ(T_FLOAT z)
{
  if (this->position_.z == z)
  {
    return;
  }
  this->position_.z = z;
  this->OnTransformChanged();
}

void Transform3D::SetScale(const TVec3f& scale)
{
  if (this->scale_ == scale)
  {
    return;
  }
  this->scale_ = scale;
  this->scale_max_ = std::max(scale.x, std::max(scale.y, std::max(scale.z, this->scale_max_)));
  this->OnScaleChanged();
}

void Transform3D::SetScale(T_FLOAT scale)
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

void Transform3D::SetScale(T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z)
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

void Transform3D::SetScaleX(T_FLOAT scale_x)
{
  if (this->scale_.x == scale_x)
  {
    return;
  }
  this->scale_.x = scale_x;
  this->scale_max_ = std::max(scale_x, this->scale_max_);
  this->OnScaleChanged();
}

void Transform3D::SetScaleY(T_FLOAT scale_y)
{
  if (this->scale_.y == scale_y)
  {
    return;
  }
  this->scale_.y = scale_y;
  this->scale_max_ = std::max(scale_y, this->scale_max_);
  this->OnScaleChanged();
}

void Transform3D::SetScaleZ(T_FLOAT scale_z)
{
  if (this->scale_.z == scale_z)
  {
    return;
  }
  this->scale_.z = scale_z;
  this->scale_max_ = std::max(scale_z, this->scale_max_);
  this->OnScaleChanged();
}
