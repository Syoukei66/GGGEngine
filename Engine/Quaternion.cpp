#include "Quaternion.h"
#include <math.h>

#include "MathConstants.h"
#include "NativeMethod.h"

// =================================================================
// Static Member
// =================================================================
const Quaternion Quaternion::Identity = Quaternion();

// =================================================================
// Constructor / Destructor
// =================================================================

Quaternion Quaternion::Eular(const TVec3f& eular_angles)
{
  return Quaternion();
}

Quaternion::Quaternion()
  : Quaternion(TVec3f(0.0f, 0.0f, 0.0f), 0.0f)
{}

Quaternion::Quaternion(const TVec3f& v, T_FLOAT rad)
{
  const T_FLOAT sin_ = sinf(rad / 2.0f);
  const T_FLOAT cos_ = cosf(rad / 2.0f);
  this->v_ = v.Normalized() * sin_;
  this->w_ = cos_;
}

// =================================================================
// Methods
// =================================================================
void Quaternion::q(const TVec3f& v, T_FLOAT rad)
{
  *this = *this * Quaternion(v, rad);
}

void Quaternion::FromRotationMatrix(LP_MATRIX_4x4 mat)
{
  const T_FLOAT m11 = NativeMethod::Matrix().Matrix4x4_Get(mat, 0, 0);
  const T_FLOAT m12 = NativeMethod::Matrix().Matrix4x4_Get(mat, 0, 1);
  const T_FLOAT m13 = NativeMethod::Matrix().Matrix4x4_Get(mat, 0, 2);

  const T_FLOAT m21 = NativeMethod::Matrix().Matrix4x4_Get(mat, 1, 0);
  const T_FLOAT m22 = NativeMethod::Matrix().Matrix4x4_Get(mat, 1, 1);
  const T_FLOAT m23 = NativeMethod::Matrix().Matrix4x4_Get(mat, 1, 2);

  const T_FLOAT m31 = NativeMethod::Matrix().Matrix4x4_Get(mat, 2, 0);
  const T_FLOAT m32 = NativeMethod::Matrix().Matrix4x4_Get(mat, 2, 1);
  const T_FLOAT m33 = NativeMethod::Matrix().Matrix4x4_Get(mat, 2, 2);

  // 最大成分を検索
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

  //elem[biggest_index]が0.0f以下になる事はないらしい。

  // 最大要素の値を算出
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

void Quaternion::ToRotationMatrix(LP_MATRIX_4x4 dest)
{
  *this = this->Normalized();
  const T_FLOAT qx = this->v_.x;
  const T_FLOAT qy = this->v_.y;
  const T_FLOAT qz = this->v_.z;
  const T_FLOAT qw = this->w_;
  //            m11 = 1.0f - 2.0f * qy * qy - 2.0f * qz * qz;
  const T_FLOAT m11 = 1.0f - 2.0f * qy * qy - 2.0f * qz * qz;
  //            m12 = 2.0f * qx * qy + 2.0f * qw * qz;
  const T_FLOAT m12 = 2.0f * qx * qy + 2.0f * qw * qz;
  //            m13 = 2.0f * qx * qz - 2.0f * qw * qy
  const T_FLOAT m13 = 2.0f * qx * qz - 2.0f * qw * qy;

  //            m21 = 2.0f * qx * qy - 2.0f * qw * qz;
  const T_FLOAT m21 = 2.0f * qx * qy - 2.0f * qw * qz;
  //            m22 = 1.0f - 2.0f * qx * qx - 2.0f * qz * qz;
  const T_FLOAT m22 = 1.0f - 2.0f * qx * qx - 2.0f * qz * qz;
  //            m23 = 2.0f * qy * qz + 2.0f * qw * qx;
  const T_FLOAT m23 = 2.0f * qy * qz + 2.0f * qw * qx;

  //            m31 = 2.0f * qx * qz + 2.0f * qw * qy;
  const T_FLOAT m31 = 2.0f * qx * qz + 2.0f * qw * qy;
  //            m32 = 2.0f * qy * qz - 2.0f * qw * qx;
  const T_FLOAT m32 = 2.0f * qy * qz - 2.0f * qw * qx;
  //            m33 = 1.0f - 2.0f * qx * qx - 2.0f * qy * qy;
  const T_FLOAT m33 = 1.0f - 2.0f * qx * qx - 2.0f * qy * qy;

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

T_FLOAT Quaternion::ScalarSquare() const
{
  return
    this->v_.x * this->v_.x +
    this->v_.y * this->v_.y +
    this->v_.z * this->v_.z +
    this->w_ * this->w_;
}

T_FLOAT Quaternion::Scalar() const
{
  return sqrtf(this->ScalarSquare());
}

const Quaternion Quaternion::Conjugated() const
{
  Quaternion ret = Quaternion();
  ret.v_ = -this->v_;
  ret.w_ = this->w_;
  return ret;
}

const Quaternion Quaternion::Inversed() const
{
  return this->Conjugated() / this->ScalarSquare();
}

const Quaternion Quaternion::Normalized() const
{
  return *this / this->ScalarSquare();
}
