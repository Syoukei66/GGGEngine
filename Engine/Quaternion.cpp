#include "Quaternion.h"
#include <math.h>
#include <algorithm>

#include "NativeAssert.h"
#include "MathConstants.h"

// =================================================================
// Constructor / Destructor
// =================================================================
const Quaternion Quaternion::LookRotation(const TVec3f& forward, const TVec3f& upwards)
{
  const TVec3f n_upwards = upwards.Normalized();
  const TVec3f z_axis = forward.Normalized();
  const TVec3f x_axis = TVec3f::OuterProduct(n_upwards, z_axis).Normalized();
  const TVec3f y_axis = TVec3f::OuterProduct(z_axis, x_axis).Normalized();
  const T_FLOAT z_dot = TVec3f::InnerProduct(TVec3f(0.0f, 0.0f, 1.0f), z_axis);
  const T_FLOAT x_dot = TVec3f::InnerProduct(TVec3f(1.0f, 0.0f, 0.0f), x_axis);
  const T_FLOAT y_dot = TVec3f::InnerProduct(TVec3f(0.0f, 1.0f, 0.0f), y_axis);
  const Quaternion x = Quaternion(TVec3f(1.0f, 0.0f, 0.0f), acosf(x_dot));
  const Quaternion y = Quaternion(TVec3f(0.0f, 1.0f, 0.0f), acosf(y_dot));
  return y;
}

// =================================================================
// Methods
// =================================================================
void Quaternion::FromRotationMatrix(const Matrix4x4& mat)
{
  const T_FLOAT m11 = mat._11;
  const T_FLOAT m12 = mat._12;
  const T_FLOAT m13 = mat._13;

  const T_FLOAT m21 = mat._21;
  const T_FLOAT m22 = mat._22;
  const T_FLOAT m23 = mat._23;

  const T_FLOAT m31 = mat._31;
  const T_FLOAT m32 = mat._32;
  const T_FLOAT m33 = mat._33;

  // 最大成分を検索
  T_FLOAT elem[4]; // 0:x, 1:y, 2:z, 3:w
  elem[0] =  m11 - m22 - m33 + 1.0f;
  elem[1] = -m11 + m22 - m33 + 1.0f;
  elem[2] = -m11 - m22 + m33 + 1.0f;
  elem[3] =  m11 + m22 + m33 + 1.0f;

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

void Quaternion::ToRotationMatrix(Matrix4x4* dest)
{
  *this = this->Normalized();
  const T_FLOAT qx = this->v_.x;
  const T_FLOAT qy = this->v_.y;
  const T_FLOAT qz = this->v_.z;
  const T_FLOAT qw = this->w_;

  dest->_11 = 1.0f - 2.0f * qy * qy - 2.0f * qz * qz;
  dest->_12 = 2.0f * qx * qy + 2.0f * qw * qz;
  dest->_13 = 2.0f * qx * qz - 2.0f * qw * qy;
  dest->_14 = 0.0f;

  dest->_21 = 2.0f * qx * qy - 2.0f * qw * qz;
  dest->_22 = 1.0f - 2.0f * qx * qx - 2.0f * qz * qz;
  dest->_23 = 2.0f * qy * qz + 2.0f * qw * qx;
  dest->_24 = 0.0f;

  dest->_31 = 2.0f * qx * qz + 2.0f * qw * qy;
  dest->_32 = 2.0f * qy * qz - 2.0f * qw * qx;
  dest->_33 = 1.0f - 2.0f * qx * qx - 2.0f * qy * qy;
  dest->_34 = 0.0f;

  dest->_41 = 0.0f;
  dest->_42 = 0.0f;
  dest->_43 = 0.0f;
  dest->_44 = 1.0f;
}
