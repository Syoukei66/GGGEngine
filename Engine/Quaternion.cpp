#include "Quaternion.h"
#include <math.h>
#include <algorithm>

#include "NativeAssert.h"
#include "MathConstants.h"

// =================================================================
// Constructor / Destructor
// =================================================================
const Quaternion Quaternion::Lerp(Quaternion a, Quaternion b, T_FLOAT t)
{
  a = a.Normalized();
  b = b.Normalized();
  NATIVE_ASSERT(a.IsNormal(), "QuaternionÇ™ê≥ãKâªÇ≥ÇÍÇƒÇ¢Ç‹ÇπÇÒ");
  NATIVE_ASSERT(b.IsNormal(), "QuaternionÇ™ê≥ãKâªÇ≥ÇÍÇƒÇ¢Ç‹ÇπÇÒ");
  if (t <= 0.0f)
  {
    return a;
  }
  if (t >= 1.0f)
  {
    return b;
  }
  const T_FLOAT r = acosf(InnerProduct(a, b));
  if (fabs(r) <= MathConstants::PI_1_2)
  {
    return (a * (1.0f - t) + b * t);
  }
  return (a * (1.0f - t) + b * -t);
}

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
void Quaternion::FromRotationMatrix(const INativeMatrix& mat)
{
  const T_FLOAT m11 = mat[0][0];
  const T_FLOAT m12 = mat[0][1];
  const T_FLOAT m13 = mat[0][2];

  const T_FLOAT m21 = mat[1][0];
  const T_FLOAT m22 = mat[1][1];
  const T_FLOAT m23 = mat[1][2];

  const T_FLOAT m31 = mat[2][0];
  const T_FLOAT m32 = mat[2][1];
  const T_FLOAT m33 = mat[2][2];

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

void Quaternion::ToRotationMatrix(INativeMatrix* dest)
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

  dest->Init();

  (*dest)[0][0] = m11;
  (*dest)[0][1] = m12;
  (*dest)[0][2] = m13;

  (*dest)[1][0] = m21;
  (*dest)[1][1] = m22;
  (*dest)[1][2] = m23;

  (*dest)[2][0] = m31;
  (*dest)[2][1] = m32;
  (*dest)[2][2] = m33;
}
