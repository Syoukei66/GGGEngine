#include "Transform3D.h"
#include <algorithm> 

#include "GameObject3D.h"
#include "MathConstants.h"

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

void Transform3D::MoveCircular(const TVec3f& move, const TVec3f& pos)
{

}

void Transform3D::MoveCircular(T_FLOAT x, T_FLOAT y, T_FLOAT z, const TVec3f& pos)
{
}

T_FLOAT Transform3D::MoveCircularX(T_FLOAT x, const TVec3f& pos)
{
  const T_FLOAT x_distance = pos.x - this->position_.x;
  const T_FLOAT z_distance = pos.z - this->position_.z;
  const T_FLOAT xz_r = sqrtf(x_distance * x_distance + z_distance * z_distance);
  //‰~Žü = 2 * PI * xz_r
  //ˆÚ“®—Êx‚Æ‰~Žü‚Ì”ä—¦ = x / ‰~Žü
  //ŠpˆÚ“®—Ê = ˆÚ“®—Êx‚Æ‰~Žü‚Ì”ä—¦ * (2 * PI)
  //        = x / ‰~Žü * (2 * PI)
  //        = x / ((2 * PI) * xz_r) * (2 * PI)
  //        = x / xz_r;
  const T_FLOAT xz_ang = atan2f(x_distance, z_distance) - x / xz_r;
  this->SetPosition(pos.x - sin(xz_ang) * xz_r, this->GetY(), pos.z - cos(xz_ang) * xz_r);
  return xz_ang;
}

T_FLOAT Transform3D::MoveCircularY(T_FLOAT y, const TVec3f& pos)
{
  return 0.0f;
}

T_FLOAT Transform3D::MoveCircularZ(T_FLOAT z, const TVec3f& pos)
{
  return 0.0f;
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
