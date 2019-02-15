#include "Quaternion.h"

// =================================================================
// Static Methods
// =================================================================
const Quaternion Quaternion::Eular(const TVec3f& eular_angles)
{
  Quaternion ret = Quaternion();
  ret = ret * Quaternion(TVec3f(0.0f, 0.0f, 1.0f), eular_angles.z);
  ret = ret.Normalized() * Quaternion(TVec3f(1.0f, 0.0f, 0.0f), eular_angles.x);
  ret = ret.Normalized() * Quaternion(TVec3f(0.0f, 1.0f, 0.0f), eular_angles.y);
  return ret;
}

const Quaternion Quaternion::Lerp(const Quaternion & a, const Quaternion & b, T_FLOAT t)
{
  if (t <= 0.0f)
  {
    return a;
  }
  if (t >= 1.0f)
  {
    return b;
  }
  const T_FLOAT r = acosf(Dot(a, b));
  if (fabs(r) <= Mathf::PI_1_2)
  {
    return (a + (b - a) * t).Normalized();
  }
  return (a + (b - a) * -t).Normalized();
}

const Quaternion Quaternion::Slerp(const Quaternion & a, const Quaternion & b, T_FLOAT t)
{
  if (t <= 0.0f)
  {
    return a;
  }
  if (t >= 1.0f)
  {
    return b;
  }
  const T_FLOAT r = acosf(Dot(a, b));
  const T_FLOAT invsin_r = 1.0f / sinf(r);
  if (fabs(r) < Mathf::PI_1_2)
  {
    return (a * (sin((1.0f - t) * r) * invsin_r) + b * (sin(t * r) * invsin_r));
  }
  return (a * (sin((1.0f - t) * r) * invsin_r) + b * -(sin(t * r) * invsin_r));
}

const Quaternion Quaternion::LookRotation(const TVec3f& forward, const TVec3f& upwards)
{
  const TVec3f n_upwards = upwards.Normalized();
  const TVec3f z_axis = forward.Normalized();
  const TVec3f x_axis = TVec3f::Cross(n_upwards, z_axis).Normalized();
  const TVec3f y_axis = TVec3f::Cross(z_axis, x_axis).Normalized();
  const T_FLOAT z_dot = TVec3f::Dot(TVec3f(0.0f, 0.0f, 1.0f), z_axis);
  const T_FLOAT x_dot = TVec3f::Dot(TVec3f(1.0f, 0.0f, 0.0f), x_axis);
  const T_FLOAT y_dot = TVec3f::Dot(TVec3f(0.0f, 1.0f, 0.0f), y_axis);
  const Quaternion x = Quaternion(TVec3f(1.0f, 0.0f, 0.0f), acosf(x_dot));
  const Quaternion y = Quaternion(TVec3f(0.0f, 1.0f, 0.0f), acosf(y_dot));
  return y;
}

GG_INLINE T_FLOAT Quaternion::Dot(const Quaternion & a, const Quaternion & b)
{
  return TVec3f::Dot(a.v, b.v) + a.w * b.w;
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

  // Å‘å¬•ª‚ðŒŸõ
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

  //elem[biggest_index]‚ª0.0fˆÈ‰º‚É‚È‚éŽ–‚Í‚È‚¢‚ç‚µ‚¢B

  // Å‘å—v‘f‚Ì’l‚ðŽZo
  float v = sqrtf(elem[biggest_index]) * 0.5f;
  float mult = 0.25f / v;

  //x
  if (biggest_index == 0)
  {
    this->v.x = v;
    this->v.y = (m12 + m21) * mult;
    this->v.z = (m31 + m13) * mult;
    this->w = (m23 - m32) * mult;
    return;
  }
  //y
  if (biggest_index == 1)
  {
    this->v.x = (m12 + m21) * mult;
    this->v.y = v;
    this->v.z = (m23 + m32) * mult;
    this->w = (m31 - m13) * mult;
    return;
  }
  //z
  if (biggest_index == 2)
  {
    this->v.x = (m31 + m13) * mult;
    this->v.y = (m23 + m32) * mult;
    this->v.z = v;
    this->w = (m12 - m21) * mult;
    return;
  }
  // w
  if (biggest_index == 3)
  {
    this->v.x = (m23 - m32) * mult;
    this->v.y = (m31 - m13) * mult;
    this->v.z = (m12 - m21) * mult;
    this->w = v;
    return;
  }
}

void Quaternion::ToRotationMatrix(Matrix4x4* dest)
{
  *this = this->Normalized();
  const T_FLOAT qx = this->v.x;
  const T_FLOAT qy = this->v.y;
  const T_FLOAT qz = this->v.z;
  const T_FLOAT qw = this->w;

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

GG_INLINE T_FLOAT Quaternion::ScalarSquare() const
{
  return
    this->v.x * this->v.x +
    this->v.y * this->v.y +
    this->v.z * this->v.z +
    this->w * this->w;
}

GG_INLINE T_FLOAT Quaternion::Scalar() const
{
  return sqrtf(this->ScalarSquare());
}

GG_INLINE const Quaternion Quaternion::Conjugated() const
{
  Quaternion ret = Quaternion();
  ret.v = -this->v;
  ret.w = this->w;
  return ret;
}

GG_INLINE const Quaternion Quaternion::Inversed() const
{
  return this->Conjugated() / this->ScalarSquare();
}

GG_INLINE const Quaternion Quaternion::Normalized() const
{
  return *this / this->Scalar();
}

GG_INLINE bool Quaternion::IsNormal(T_FLOAT eps) const
{
  return fabs(1.0f - this->Scalar()) < eps;
}
