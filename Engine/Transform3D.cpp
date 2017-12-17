#include "Transform3D.h"
#include "GameObject3D.h"
#include "NativeMethod.h"
#include "MathConstants.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Transform3D::Transform3D(GameObject3D* entity)
  : Transform(entity)
  , entity_(entity)
  , direction_()
  , position_()
  , scale_()
  , world_position_()
  , matrix_applied_position_()
{
  this->rotator_ = new Transform3DRotator(this);
  this->world_matrix_ = NativeMethod::Matrix().Matrix4x4_Create();
}

Transform3D::~Transform3D()
{
  delete this->rotator_;
  NativeMethod::Matrix().Matrix4x4_Delete(this->world_matrix_);
}

// =================================================================
// Method
// =================================================================
void Transform3D::OnInit()
{
  this->position_ = TVec3f(0.0f, 0.0f, 0.0f);
  this->scale_ = TVec3f(1.0f, 1.0f, 1.0f);
  this->rotator_->SetEularAngles(TVec3f(0.0f, 0.0f, 0.0f));

  this->world_position_ = TVec3f(0.0f, 0.0f, 0.0f);
  this->matrix_applied_position_ = TVec3f(0.0f, 0.0f, 0.0f);
}

void Transform3D::Move(const TVec3f& value)
{
  TVec3f v = value;
  NativeMethod::Matrix().Matrix4x4_Apply(this->GetRotationMatrix(), &v.x, &v.y, &v.z);
  const TVec3f& pos = this->GetPosition();
  this->SetPosition(pos.x + v.x, pos.y + v.y, pos.z + v.z);
}

void Transform3D::Move(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  NativeMethod::Matrix().Matrix4x4_Apply(this->GetRotationMatrix(), &x, &y, &z);
  const TVec3f& pos = this->GetPosition();
  this->SetPosition(pos.x + x, pos.y + y, pos.z + z);
}

void Transform3D::MoveX(T_FLOAT x)
{
  T_FLOAT y = 0.0f;
  T_FLOAT z = 0.0f;
  NativeMethod::Matrix().Matrix4x4_Apply(this->GetRotationMatrix(), &x, &y, &z);
  this->SetPosition(this->GetX() + x, this->GetY() + y, this->GetZ() + z);
}

void Transform3D::MoveY(T_FLOAT y)
{
  T_FLOAT x = 0.0f;
  T_FLOAT z = 0.0f;
  NativeMethod::Matrix().Matrix4x4_Apply(this->GetRotationMatrix(), &x, &y, &z);
  this->SetPosition(this->GetX() + x, this->GetY() + y, this->GetZ() + z);
}

void Transform3D::MoveZ(T_FLOAT z)
{
  T_FLOAT x = 0.0f;
  T_FLOAT y = 0.0f;
  NativeMethod::Matrix().Matrix4x4_Apply(this->GetRotationMatrix(), &x, &y, &z);
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

void Transform3D::OnRotationChanged()
{
  Transform::OnRotationChanged();
  //this->quaternion_.
}

void Transform3D::UpdateWorldMatrix(LP_MATRIX_4x4 matrix)
{
  NativeMethod::Matrix().Matrix4x4_Assign(this->world_matrix_, matrix);
}

void Transform3D::UpdateTranslateMatrix(LP_MATRIX_4x4 matrix)
{
  NativeMethod::Matrix().Matrix4x4_Translate(
    matrix,
    this->position_.x,
    this->position_.y,
    this->position_.z
  );
}

void Transform3D::UpdateScaleMatrix(LP_MATRIX_4x4 matrix)
{
  NativeMethod::Matrix().Matrix4x4_Scaling(
    matrix,
    this->scale_.x,
    this->scale_.y,
    this->scale_.z
  );
}

void Transform3D::UpdateRotateMatrix(LP_MATRIX_4x4 matrix)
{
  this->rotator_->ToRotationMatrix(matrix);
}

void Transform3D::OnUpdateMatrix(LP_MATRIX_4x4 matrix)
{
  this->matrix_applied_position_.x = 0.0f;
  this->matrix_applied_position_.y = 0.0f;
  this->matrix_applied_position_.z = 0.0f;
  NativeMethod::Matrix().Matrix4x4_Apply(
    matrix,
    &this->matrix_applied_position_.x,
    &this->matrix_applied_position_.y,
    &this->matrix_applied_position_.z
  );
  NativeMethod::Matrix().Matrix4x4_Direction(matrix, &this->direction_);
}

// =================================================================
// setter/getter
// =================================================================
const TVec3f& Transform3D::GetMatrixAppliedPosition()
{
  this->UpdateMatrix();
  return this->matrix_applied_position_;
}

void Transform3D::ApplyMatrixToPosition(TVec3f* dest)
{
  NativeMethod::Matrix().Matrix4x4_Apply(
    this->GetMatrix(),
    &(dest->x),
    &(dest->y),
    &(dest->z)
  );
}

const TVec3f& Transform3D::GetWorldPosition(GameObject3D* root)
{
  if (this->world_position_dirty_)
  {
    this->world_position_.x = 0.0f;
    this->world_position_.y = 0.0f;
    this->world_position_.z = 0.0f;
    this->entity_->ConvertPositionLocalToWorld(nullptr, &this->world_position_, root);
    this->world_position_dirty_ = false;
  }
  return this->world_position_;
}

T_FLOAT Transform3D::GetWorldX(GameObject3D* root)
{
  return this->GetWorldPosition(root).x;
}

T_FLOAT Transform3D::GetWorldY(GameObject3D* root)
{
  return this->GetWorldPosition(root).y;
}

T_FLOAT Transform3D::GetWorldZ(GameObject3D* root)
{
  return this->GetWorldPosition(root).z;
}

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
  this->OnScaleChanged();
}

void Transform3D::SetScaleX(T_FLOAT scale_x)
{
  if (this->scale_.x == scale_x)
  {
    return;
  }
  this->scale_.x = scale_x;
  this->OnScaleChanged();
}

void Transform3D::SetScaleY(T_FLOAT scale_y)
{
  if (this->scale_.y == scale_y)
  {
    return;
  }
  this->scale_.y = scale_y;
  this->OnScaleChanged();
}

void Transform3D::SetScaleZ(T_FLOAT scale_z)
{
  if (this->scale_.z == scale_z)
  {
    return;
  }
  this->scale_.z = scale_z;
  this->OnScaleChanged();
}
