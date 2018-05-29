#include "Transform3D.h"
#include <algorithm> 

#include "GameObject3D.h"
#include "MathConstants.h"
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
// Method
// =================================================================
void Transform3D::OnInit()
{
  this->position_ = TVec3f(0.0f, 0.0f, 0.0f);
  this->scale_ = TVec3f(1.0f, 1.0f, 1.0f);
  this->rotator_->Init();
}

void Transform3D::Move(const TVec3f& value)
{
  TVec3f v = value;
  this->GetRotationMatrix().Apply(&v);
  const TVec3f& pos = this->GetPosition();
  this->SetPosition(pos.x + v.x, pos.y + v.y, pos.z + v.z);
}

void Transform3D::Move(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  this->GetRotationMatrix().Apply(&x, &y, &z);
  const TVec3f& pos = this->GetPosition();
  this->SetPosition(pos.x + x, pos.y + y, pos.z + z);
}

void Transform3D::MoveX(T_FLOAT x)
{
  T_FLOAT y = 0.0f;
  T_FLOAT z = 0.0f;
  this->GetRotationMatrix().Apply(&x, &y, &z);
  this->SetPosition(this->GetX() + x, this->GetY() + y, this->GetZ() + z);
}

void Transform3D::MoveY(T_FLOAT y)
{
  T_FLOAT x = 0.0f;
  T_FLOAT z = 0.0f;
  this->GetRotationMatrix().Apply(&x, &y, &z);
  this->SetPosition(this->GetX() + x, this->GetY() + y, this->GetZ() + z);
}

void Transform3D::MoveZ(T_FLOAT z)
{
  T_FLOAT x = 0.0f;
  T_FLOAT y = 0.0f;
  this->GetRotationMatrix().Apply(&x, &y, &z);
  this->SetPosition(this->GetX() + x, this->GetY() + y, this->GetZ() + z);
}

void Transform3D::LookAt(const TVec3f& target, const TVec3f& up)
{
  const TVec3f z = (target - this->GetWorldPosition()).Normalized();
  const TVec3f x = TVec3f::OuterProduct(up, z);
  const TVec3f y = TVec3f::OuterProduct(z, x);

  INativeMatrix* mat = INativeMatrix::Create();
  (*mat)[0][0] = x.x;  (*mat)[1][0] = y.x;  (*mat)[2][0] = z.x;
  (*mat)[0][1] = x.y;  (*mat)[1][1] = y.y;  (*mat)[2][1] = z.y;
  (*mat)[0][2] = x.z;  (*mat)[1][2] = y.z;  (*mat)[2][2] = z.z;
  this->rotator_->FromRotationMatrix(mat);

  delete mat;
}

void Transform3D::UpdateTranslateMatrix(INativeMatrix* matrix)
{
  matrix->Translation(this->position_);
}

void Transform3D::UpdateScaleMatrix(INativeMatrix* matrix)
{
  matrix->Scaling(this->scale_);
}

void Transform3D::UpdateRotateMatrix(INativeMatrix* matrix)
{
  this->rotator_->ToRotationMatrix(matrix);
}

const INativeMatrix* Transform3D::GetParentWorldMatrix()
{
  GameObject3D* parent = this->entity_->GetParent();
  if (!parent)
  {
    return nullptr;
  }
  return &parent->GetTransform()->GetWorldMatrix();
}

// =================================================================
// setter/getter
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
