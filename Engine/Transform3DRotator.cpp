#include "Transform3DRotator.h"
#include <math.h>

#include "MathConstants.h"
#include "NativeMethod.h"
#include "GameObject3D.h"

static const TVec3f X_AXIS = TVec3f(1.0f, 0.0f, 0.0f);
static const TVec3f Y_AXIS = TVec3f(0.0f, 1.0f, 0.0f);
static const TVec3f Z_AXIS = TVec3f(0.0f, 0.0f, 1.0f);

// =================================================================
// Constructor / Destructor
// =================================================================
Transform3DRotator::Transform3DRotator(Transform3D* transform)
  : transform_(transform)
  , quaternion_()
  , eular_angles_(0.0f, 0.0f, 0.0f)
  , need_rotation_matrix_update_(false)
  , need_eular_angles_update_(false)
{
  this->rotation_matrix_ = NativeMethod::Matrix().Matrix4x4_Create();
}

Transform3DRotator::~Transform3DRotator()
{
  NativeMethod::Matrix().Matrix4x4_Delete(this->rotation_matrix_);
}

// =================================================================
// Methods
// =================================================================
void Transform3DRotator::RotateX(T_FLOAT rad)
{
  if (rad == 0.0f)
  {
    return;
  }
  this->q(X_AXIS, rad);
}

void Transform3DRotator::RotateY(T_FLOAT rad)
{
  if (rad == 0.0f)
  {
    return;
  }
  this->q(Y_AXIS, rad);
}

void Transform3DRotator::RotateZ(T_FLOAT rad)
{
  if (rad == 0.0f)
  {
    return;
  }
  this->q(Z_AXIS, rad);
}

void Transform3DRotator::FromRotationMatrix(LP_MATRIX_4x4 matrix)
{
  NativeMethod::Matrix().Matrix4x4_Assign(this->rotation_matrix_, matrix);
  this->FromRotationMatrix();
}

void Transform3DRotator::ToRotationMatrix(LP_MATRIX_4x4 dest)
{
  this->PrepareRotationMatrix();
  NativeMethod::Matrix().Matrix4x4_Assign(dest, this->rotation_matrix_);
  //this->PrepareEularAngles();
  //NativeMethod::Matrix().Matrix4x4_Rotation(dest, this->eular_angles_.x, this->eular_angles_.y, this->eular_angles_.z);
}

const void Transform3DRotator::q(const TVec3f& v, T_FLOAT rad)
{
  if (rad == 0.0f)
  {
    return;
  }
  this->quaternion_.q(v, rad);
  this->transform_->OnRotationChanged();
  this->need_rotation_matrix_update_ = true;
  this->need_eular_angles_update_ = true;
}

void Transform3DRotator::FromRotationMatrix()
{
  this->quaternion_.FromRotationMatrix(this->rotation_matrix_);
  this->transform_->OnRotationChanged();
  this->need_rotation_matrix_update_ = false;
  this->need_eular_angles_update_ = true;
}

void Transform3DRotator::PrepareRotationMatrix()
{
  if (!this->need_rotation_matrix_update_)
  {
    return;
  }
  this->quaternion_.ToRotationMatrix(this->rotation_matrix_);
  this->need_eular_angles_update_ = true;
  this->need_rotation_matrix_update_ = false;
}

void Transform3DRotator::PrepareEularAngles()
{
  this->PrepareRotationMatrix();
  if (!this->need_eular_angles_update_)
  {
    return;
  }
  const T_FLOAT m11 = NativeMethod::Matrix().Matrix4x4_Get(this->rotation_matrix_, 0, 0);
  const T_FLOAT m12 = NativeMethod::Matrix().Matrix4x4_Get(this->rotation_matrix_, 0, 1);
  const T_FLOAT m13 = NativeMethod::Matrix().Matrix4x4_Get(this->rotation_matrix_, 0, 2);

  const T_FLOAT m21 = NativeMethod::Matrix().Matrix4x4_Get(this->rotation_matrix_, 1, 0);
  const T_FLOAT m22 = NativeMethod::Matrix().Matrix4x4_Get(this->rotation_matrix_, 1, 1);
  const T_FLOAT m23 = NativeMethod::Matrix().Matrix4x4_Get(this->rotation_matrix_, 1, 2);

  const T_FLOAT m31 = NativeMethod::Matrix().Matrix4x4_Get(this->rotation_matrix_, 2, 0);
  const T_FLOAT m32 = NativeMethod::Matrix().Matrix4x4_Get(this->rotation_matrix_, 2, 1);
  const T_FLOAT m33 = NativeMethod::Matrix().Matrix4x4_Get(this->rotation_matrix_, 2, 2);

  if (m32 == 1.0f)
  {
    this->eular_angles_.x = MathConstants::PI_1_2;
    this->eular_angles_.y = 0.0f;
    this->eular_angles_.z = atan2f(m21, m11);
  }
  else if (m32 == -1.0f)
  {
    this->eular_angles_.x = -MathConstants::PI_1_2;
    this->eular_angles_.y = 0.0f;
    this->eular_angles_.z = atan2f(m21, m11);
  }
  else
  {
    this->eular_angles_.x = asinf(m32);
    this->eular_angles_.y = atan2f(-m31, m33);
    this->eular_angles_.z = atan2f(-m12, m22);
  }

  this->need_eular_angles_update_ = false;
}


void Transform3DRotator::SetEularAngles(const TVec3f& rotation)
{
  NativeMethod::Matrix().Matrix4x4_Rotation(this->rotation_matrix_, rotation.x, rotation.y, rotation.z);

  this->FromRotationMatrix();

  this->eular_angles_ = rotation;
  this->need_eular_angles_update_ = false;
}

void Transform3DRotator::SetEularAngles(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  NativeMethod::Matrix().Matrix4x4_Rotation(this->rotation_matrix_, x, y, z);

  this->FromRotationMatrix();

  this->eular_angles_.x = x;
  this->eular_angles_.y = y;
  this->eular_angles_.z = z;
  this->need_eular_angles_update_ = false;
}

void Transform3DRotator::SetEularX(T_FLOAT x)
{
  NativeMethod::Matrix().Matrix4x4_Rotation(this->rotation_matrix_, x, this->eular_angles_.y, this->eular_angles_.z);

  this->FromRotationMatrix();
}

void Transform3DRotator::SetEularY(T_FLOAT y)
{
  NativeMethod::Matrix().Matrix4x4_Rotation(this->rotation_matrix_, this->eular_angles_.x, y, this->eular_angles_.z);

  this->FromRotationMatrix();
}

void Transform3DRotator::SetEularZ(T_FLOAT z)
{
  NativeMethod::Matrix().Matrix4x4_Rotation(this->rotation_matrix_, this->eular_angles_.x, this->eular_angles_.y, z);

  this->FromRotationMatrix();
}
