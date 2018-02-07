#include "Quaternion.h"
#include <math.h>
#include <algorithm>

#include "NativeAssert.h"
#include "MathConstants.h"

// =================================================================
// Static Member
// =================================================================
const Quaternion Quaternion::Identity = Quaternion();

// =================================================================
// Constructor / Destructor
// =================================================================

const Quaternion Quaternion::Eular(const TVec3f& eular_angles)
{
  Quaternion ret = Quaternion();
  ret.q(TVec3f(0.0f, 0.0f, 1.0f), eular_angles.z);
  ret.q(TVec3f(1.0f, 0.0f, 0.0f), eular_angles.x);
  ret.q(TVec3f(0.0f, 1.0f, 0.0f), eular_angles.y);
  return ret;
}

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

const Quaternion Quaternion::Slerp(Quaternion a, Quaternion b, T_FLOAT t)
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
  const T_FLOAT invsin_r = 1.0f / sinf(r);
  if (fabs(r) < MathConstants::PI_1_2)
  {
    return (a * (sin((1.0f - t) * r) * invsin_r) + b * (sin(t * r) * invsin_r));
  }
  return (a * (sin((1.0f - t) * r) * invsin_r) + b * -(sin(t * r) * invsin_r));
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

T_FLOAT Quaternion::InnerProduct(const Quaternion& a, const Quaternion& b)
{
  return TVec3f::InnerProduct(a.v_, b.v_) + a.w_ * b.w_;
}

Quaternion::Quaternion()
  : Quaternion(TVec3f(0.0f, 0.0f, 0.0f), 1.0f)
{}

Quaternion::Quaternion(const TVec3f& v, T_FLOAT rad)
{
  const T_FLOAT sin_ = sinf(rad / 2.0f);
  const T_FLOAT cos_ = cosf(rad / 2.0f);
  this->v_ = v.Normalized() * sin_;
  this->w_ = cos_;
}

Quaternion::Quaternion(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT w)
  : v_(x, y, z)
  , w_(w)
{}

// =================================================================
// Methods
// =================================================================
void Quaternion::q(const TVec3f& v, T_FLOAT rad)
{
  *this = this->Normalized() * Quaternion(v, rad);
}

void Quaternion::FromEularAngles(const TVec3f& mat)
{
  const T_FLOAT sin_ = sinf(0.0f);
  const T_FLOAT cos_ = cosf(0.0f);
  this->v_ = mat.Normalized() * sin_;
  this->w_ = cos_;
  float cosY = cosf(mat.y / 2.0f);
  float sinY = sinf(mat.y / 2.0f);
  float cosP = cosf(mat.x / 2.0f);
  float sinP = sinf(mat.x / 2.0f);
  float cosR = cosf(mat.z / 2.0f);
  float sinR = sinf(mat.z / 2.0f);
  this->v_.x = cosR * sinP * cosY + sinR * cosP * sinY;
  this->v_.y = cosR * cosP * sinY - sinR * sinP * cosY;
  this->v_.z = sinR * cosP * cosY - cosR * sinP * sinY;
  this->w_ = cosR * cosP * cosY + sinR * sinP * sinY;
}

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
  return *this / this->Scalar();
}

bool Quaternion::IsNormal(T_FLOAT eps) const
{
  return fabs(1.0f - this->Scalar()) < eps;
}
