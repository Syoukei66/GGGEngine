#include "Quaternion.h"
#include <math.h>

#include "MathConstants.h"
#include "NativeMethod.h"

static const TVec3f X_AXIS = TVec3f(1.0f, 0.0f, 0.0f);
static const TVec3f Y_AXIS = TVec3f(0.0f, 1.0f, 0.0f);
static const TVec3f Z_AXIS = TVec3f(0.0f, 0.0f, 1.0f);

// =================================================================
// Static Member
// =================================================================
const Quaternion Quaternion::Identity = Quaternion();

// =================================================================
// Constructor / Destructor
// =================================================================
Quaternion::Quaternion()
  : v_(0.0f, 0.0f, 0.0f)
  , w_(1.0f)
  , eular_angles_(0.0f, 0.0f, 0.0f)
  , is_normalized_(true)
{
}

Quaternion::~Quaternion()
{
}

// =================================================================
// Method
// =================================================================
void Quaternion::RotationXAxis(T_FLOAT rad)
{
  this->q(X_AXIS, rad);
}

void Quaternion::RotationYAxis(T_FLOAT rad)
{
  this->q(Y_AXIS, rad);
}

void Quaternion::RotationZAxis(T_FLOAT rad)
{
  this->q(Z_AXIS, rad);
}

void Quaternion::RotationX(const TVec3f& direction, T_FLOAT rad)
{
  TVec3f v = direction;
  v.x = direction.z;
  v.z = direction.x;
  this->q(direction, rad);
}

void Quaternion::RotationY(const TVec3f& direction, T_FLOAT rad)
{
  TVec3f v = direction;
  v.y = direction.z;
  v.z = direction.y;
  this->q(direction, rad);
}

void Quaternion::RotationZ(const TVec3f& direction, T_FLOAT rad)
{
  this->q(direction, rad);
}

const TVec3f& Quaternion::EularAngles()
{
  if (!this->is_normalized_)
  {
    *this = Normalized(*this);
    this->is_normalized_ = true;
    this->eular_angles_ = this->v_ * (MathConstants::PI * 2);
  }
  return this->eular_angles_;
}

void Quaternion::SetRotationWithAxis(const TVec3f rotation)
{

}

void Quaternion::SetRotationWithAxis(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
}

const TVec3f Quaternion::q(const TVec3f& v, T_FLOAT rad)
{
  const T_FLOAT sin_ = sin(rad / 2.0f);
  const T_FLOAT cos_ = cos(rad / 2.0f);
  this->v_ * sin_;
  this->w_ = cos_;
}

void Quaternion::ToRotationMatrix(LP_MATRIX_4x4 dest) const
{
  //            m11 = 1.0f - 2.0f * qy * qy - 2.0f * qz * qz;
  const T_FLOAT m11 = 1.0f - 2.0f * this->v_.y * this->v_.y - 2.0f * this->v_.z * this->v_.z;
  //            m12 = 2.0f * qx * qy + 2.0f * qw * qz;
  const T_FLOAT m12 = 2.0f * this->v_.x * this->v_.y + 2.0f * this->w_ * this->v_.z;
  //            m13 = 2.0f * qx * qz - 2.0f * qw * qy
  const T_FLOAT m13 = 2.0f * this->v_.x * this->v_.z - 2.0f * this->w_ * this->v_.y;

  //            m21 = 2.0f * qx * qy - 2.0f * qw * qz;
  const T_FLOAT m21 = 2.0f * this->v_.x * this->v_.y - 2.0f * this->w_ * this->v_.z;
  //            m22 = 1.0f - 2.0f * qx * qx - 2.0f * qz * qz;
  const T_FLOAT m22 = 1.0f - 2.0f * this->v_.x * this->v_.x - 2.0f * this->v_.z * this->v_.z;
  //            m23 = 2.0f * qy * qz + 2.0f * qw * qx;
  const T_FLOAT m23 = 2.0f * this->v_.y * this->v_.z + 2.0f * this->w_ * this->v_.x;

  //            m31 = 2.0f * qx * qz + 2.0f * qw * qy;
  const T_FLOAT m31 = 2.0f * this->v_.x * this->v_.z + 2.0f * this->w_ * this->v_.y;
  //            m32 = 2.0f * qy * qz - 2.0f * qw * qx;
  const T_FLOAT m32 = 2.0f * this->v_.y * this->v_.z - 2.0f * this->w_ * this->v_.x;
  //            m33 = 1.0f - 2.0f * qx * qx - 2.0f * qy * qy;
  const T_FLOAT m33 = 1.0f - 2.0f * this->v_.x * this->v_.x - 2.0f * this->v_.y * this->v_.y;

  NativeMethod::Matrix().Matrix4x4_Init(dest);

  NativeMethod::Matrix().Matrix4x4_Set(dest, 0, 0, m11);
  NativeMethod::Matrix().Matrix4x4_Set(dest, 0, 1, m12);
  NativeMethod::Matrix().Matrix4x4_Set(dest, 0, 2, m13);

  NativeMethod::Matrix().Matrix4x4_Set(dest, 1, 0, m21);
  NativeMethod::Matrix().Matrix4x4_Set(dest, 1, 1, m22);
  NativeMethod::Matrix().Matrix4x4_Set(dest, 1, 2, m23);

  NativeMethod::Matrix().Matrix4x4_Set(dest, 2, 0, m31);
  NativeMethod::Matrix().Matrix4x4_Set(dest, 2, 1, m32);
  NativeMethod::Matrix().Matrix4x4_Set(dest, 2, 2, m33);
}

void Quaternion::FromRotationMatrix(LP_MATRIX_4x4 rotation_matrix)
{
  const T_FLOAT m11 = NativeMethod::Matrix().Matrix4x4_Get(rotation_matrix, 0, 0);
  const T_FLOAT m12 = NativeMethod::Matrix().Matrix4x4_Get(rotation_matrix, 0, 1);
  const T_FLOAT m13 = NativeMethod::Matrix().Matrix4x4_Get(rotation_matrix, 0, 2);

  const T_FLOAT m21 = NativeMethod::Matrix().Matrix4x4_Get(rotation_matrix, 1, 0);
  const T_FLOAT m22 = NativeMethod::Matrix().Matrix4x4_Get(rotation_matrix, 1, 1);
  const T_FLOAT m23 = NativeMethod::Matrix().Matrix4x4_Get(rotation_matrix, 1, 2);

  const T_FLOAT m31 = NativeMethod::Matrix().Matrix4x4_Get(rotation_matrix, 2, 0);
  const T_FLOAT m32 = NativeMethod::Matrix().Matrix4x4_Get(rotation_matrix, 2, 1);
  const T_FLOAT m33 = NativeMethod::Matrix().Matrix4x4_Get(rotation_matrix, 2, 2);

  // ç≈ëÂê¨ï™Çåüçı
  T_FLOAT elem[4]; // 0:x, 1:y, 2:z, 3:w
  elem[0] = m11 - m22 - m33 + 1.0f;
  elem[1] = -m11 + m22 - m33 + 1.0f;
  elem[2] = -m11 - m22 + m33 + 1.0f;
  elem[3] = m11 + m22 + m33 + 1.0f;

  T_UINT8 biggest_index = 0;
  for (T_UINT8 i = 1; i < 4; ++i) {
    if (elem[i] > elem[biggest_index])
    {
      biggest_index = i;
    }
  }

  //elem[biggest_index]Ç™0.0fà»â∫Ç…Ç»ÇÈéñÇÕÇ»Ç¢ÇÁÇµÇ¢ÅB

  // ç≈ëÂóvëfÇÃílÇéZèo
  float v = sqrtf(elem[biggest_index]) * 0.5f;
  float mult = 0.25f / v;

  //x
  if (biggest_index == 0)
  {
    this->v_.x = v;
    this->v_.y = (m12 + m21) * mult;
    this->v_.z = (m31 + m13) * mult;
    this->w_ = (m23 - m32) * mult;
    return;
  }
  //y
  if (biggest_index == 1)
  {
    this->v_.x = (m12 + m21) * mult;
    this->v_.y = v;
    this->v_.z = (m23 + m32) * mult;
    this->w_ = (m31 - m13) * mult;
    return;
  }
  //z
  if (biggest_index == 2)
  {
    this->v_.x = (m31 + m13) * mult;
    this->v_.y = (m23 + m32) * mult;
    this->v_.z = v;
    this->w_ = (m12 - m21) * mult;
    return;
  }
  // w
  if (biggest_index == 3)
  {
    this->v_.x = (m23 - m32) * mult;
    this->v_.y = (m31 - m13) * mult;
    this->v_.z = (m12 - m21) * mult;
    this->w_ = v;
    return;
  }
}

T_FLOAT Quaternion::ScalarSquare(const Quaternion& q)
{
  return
    q.v_.x * q.v_.x +
    q.v_.y * q.v_.y +
    q.v_.z * q.v_.z +
    q.w_ * q.w_;
}

T_FLOAT Quaternion::Scalar(const Quaternion& q)
{
  return sqrt(ScalarSquare(q));
}

const Quaternion Quaternion::Conjugated(const Quaternion& q)
{
  Quaternion ret = Quaternion();
  ret.v_ = -q.v_;
  ret.w_ = q.w_;
  return ret;
}

const Quaternion Quaternion::Inversed(const Quaternion& q)
{
  return Conjugated(q) / ScalarSquare(q);
}

const Quaternion Quaternion::Normalized(const Quaternion& q)
{
  return q / ScalarSquare(q);
}
