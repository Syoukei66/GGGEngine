#include "Transform3DRotator.h"
#include <math.h>

#include "MathConstants.h"
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
  this->rotation_matrix_ = INativeMatrix::Create();
}

Transform3DRotator::~Transform3DRotator()
{
  delete this->rotation_matrix_;
}

// =================================================================
// Methods
// =================================================================
void Transform3DRotator::Init()
{
  this->quaternion_ = Quaternion();
  this->eular_angles_ = TVec3f(0.0f, 0.0f, 0.0f);
  this->rotation_matrix_->Init();
  this->need_rotation_matrix_update_ = false;
  this->need_eular_angles_update_ = false;
}

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

void Transform3DRotator::RotateXAxis(T_FLOAT rad)
{
  this->SetEularX(this->GetEularX() + rad * MathConstants::RAD_TO_DEG);
}

void Transform3DRotator::RotateYAxis(T_FLOAT rad)
{
  this->SetEularY(this->GetEularY() + rad * MathConstants::RAD_TO_DEG);
}

void Transform3DRotator::RotateZAxis(T_FLOAT rad)
{
  this->SetEularZ(this->GetEularZ() + rad * MathConstants::RAD_TO_DEG);
}

void Transform3DRotator::FromRotationMatrix(INativeMatrix* matrix)
{
  this->rotation_matrix_->Assign(*matrix);
  this->FromRotationMatrix();
}

void Transform3DRotator::ToRotationMatrix(INativeMatrix* dest)
{
  this->PrepareRotationMatrix();
  dest->Assign(*this->rotation_matrix_);
}

void Transform3DRotator::Lerp(const Quaternion& a, const Quaternion& b, T_FLOAT t)
{
  Quaternion lerped = Quaternion::Lerp(a, b, t);
  if (this->quaternion_ == lerped)
  {
    return;
  }
  this->quaternion_ = lerped;
  this->transform_->OnRotationChanged();
  this->need_rotation_matrix_update_ = true;
  this->need_eular_angles_update_ = true;
}

void Transform3DRotator::Lerp(const Quaternion& b, T_FLOAT t)
{
  if (t <= 0.0f)
  {
    return;
  }
  Quaternion lerped = Quaternion::Lerp(this->quaternion_, b, t);
  if (this->quaternion_ == lerped)
  {
    return;
  }
  this->quaternion_ = lerped;
  this->transform_->OnRotationChanged();
  this->need_rotation_matrix_update_ = true;
  this->need_eular_angles_update_ = true;
}

void Transform3DRotator::Slerp(const Quaternion& a, const Quaternion& b, T_FLOAT t)
{
  Quaternion slerped = Quaternion::Slerp(a, b, t);
  if (this->quaternion_ == slerped)
  {
    return;
  }
  this->quaternion_ = slerped;
  this->transform_->OnRotationChanged();
  this->need_rotation_matrix_update_ = true;
  this->need_eular_angles_update_ = true;
}

void Transform3DRotator::Slerp(const Quaternion& b, T_FLOAT t)
{
  if (t <= 0.0f)
  {
    return;
  }
  Quaternion slerped = Quaternion::Slerp(this->quaternion_, b, t);
  if (this->quaternion_ == slerped)
  {
    return;
  }
  this->quaternion_ = slerped;
  this->transform_->OnRotationChanged();
  this->need_rotation_matrix_update_ = true;
  this->need_eular_angles_update_ = true;
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
  this->quaternion_.FromRotationMatrix(*this->rotation_matrix_);
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
  const T_FLOAT m11 = (*this->rotation_matrix_)[0][0];
  const T_FLOAT m12 = (*this->rotation_matrix_)[0][1];
  const T_FLOAT m13 = (*this->rotation_matrix_)[0][2];

  const T_FLOAT m21 = (*this->rotation_matrix_)[1][0];
  const T_FLOAT m22 = (*this->rotation_matrix_)[1][1];
  const T_FLOAT m23 = (*this->rotation_matrix_)[1][2];

  const T_FLOAT m31 = (*this->rotation_matrix_)[2][0];
  const T_FLOAT m32 = (*this->rotation_matrix_)[2][1];
  const T_FLOAT m33 = (*this->rotation_matrix_)[2][2];

  const float eps = 0.001f;
  if (fabs(m32 - 1.0f) < eps)
  {
    this->eular_angles_.x = MathConstants::PI_1_2;
    this->eular_angles_.y = 0.0f;
    this->eular_angles_.z = atan2f(m21, m11);
  }
  else if (fabs(m32 + 1.0f) < eps)
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

  this->eular_angles_ *= MathConstants::RAD_TO_DEG;
  this->need_eular_angles_update_ = false;
}


void Transform3DRotator::SetEularAngles(const TVec3f& rotation)
{
  this->rotation_matrix_->Rotation(rotation * MathConstants::DEG_TO_RAD);

  this->FromRotationMatrix();

  this->eular_angles_ = rotation;
  this->need_eular_angles_update_ = false;
}

void Transform3DRotator::SetEularAngles(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  this->rotation_matrix_->Rotation(
    x * MathConstants::DEG_TO_RAD,
    y * MathConstants::DEG_TO_RAD,
    z * MathConstants::DEG_TO_RAD
  );

  this->FromRotationMatrix();

  this->eular_angles_.x = x;
  this->eular_angles_.y = y;
  this->eular_angles_.z = z;
  this->need_eular_angles_update_ = false;
}

void Transform3DRotator::SetEularX(T_FLOAT x)
{
  this->rotation_matrix_->Rotation(
    x * MathConstants::DEG_TO_RAD,
    this->eular_angles_.y * MathConstants::DEG_TO_RAD,
    this->eular_angles_.z * MathConstants::DEG_TO_RAD
  );

  this->FromRotationMatrix();

  this->eular_angles_.x = x;
  this->need_eular_angles_update_ = false;
}

void Transform3DRotator::SetEularY(T_FLOAT y)
{
  this->rotation_matrix_->Rotation(
    this->eular_angles_.x * MathConstants::DEG_TO_RAD,
    y * MathConstants::DEG_TO_RAD,
    this->eular_angles_.z * MathConstants::DEG_TO_RAD
  );

  this->FromRotationMatrix();

  this->eular_angles_.y = y;
  this->need_eular_angles_update_ = false;
}

void Transform3DRotator::SetEularZ(T_FLOAT z)
{
  this->rotation_matrix_->Rotation(
    this->eular_angles_.x * MathConstants::DEG_TO_RAD,
    this->eular_angles_.y * MathConstants::DEG_TO_RAD,
    z * MathConstants::DEG_TO_RAD
  );

  this->FromRotationMatrix();

  this->eular_angles_.z = z;
  this->need_eular_angles_update_ = false;
}
