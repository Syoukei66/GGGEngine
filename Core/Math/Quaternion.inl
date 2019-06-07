#pragma once

// =================================================================
// Constructor / Destructor
// =================================================================
GG_INLINE Quaternion::Quaternion()
  : v(0.0f, 0.0f, 0.0f)
  , w(1.0f)
{}

GG_INLINE Quaternion::Quaternion(const TVec3f& v, T_FLOAT rad)
  : v(v.Normalized() * sinf(rad / 2.0f))
  , w(cosf(rad / 2.0f))
{}

GG_INLINE Quaternion::Quaternion(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT w)
  : Quaternion(TVec3f(x, y, z), w)
{}

GG_INLINE Quaternion::Quaternion(const Quaternion& q)
  : v(q.v)
  , w(q.w)
{}

// =================================================================
// Operator
// =================================================================
// ‘ã“ü
GG_INLINE Quaternion& Quaternion::operator=(const Quaternion& other)
{
  this->v = other.v;
  this->w = other.w;
  return *this;
}

// ‰ÁŽZ
GG_INLINE const Quaternion Quaternion::operator+ () const
{
  return *this;
}
GG_INLINE const Quaternion Quaternion::operator+ (const Quaternion& other) const
{
  Quaternion ret = *this;
  ret.v += other.v;
  ret.w += other.w;
  return ret;
}
GG_INLINE Quaternion& Quaternion::operator+= (const Quaternion& other)
{
  this->v += other.v;
  this->w += other.w;
  return *this;
}

// Œ¸ŽZ
GG_INLINE const Quaternion Quaternion::operator- () const
{
  Quaternion ret = *this;
  ret.v = -ret.v;
  ret.w = -ret.w;
  return ret;
}
GG_INLINE const Quaternion Quaternion::operator- (const Quaternion& other) const
{
  Quaternion ret = *this;
  ret.v -= other.v;
  ret.w -= other.w;
  return ret;
}
GG_INLINE Quaternion& Quaternion::operator-= (const Quaternion& other)
{
  this->v -= other.v;
  this->w -= other.w;
  return *this;
}

// æŽZ
GG_INLINE const Quaternion Quaternion::operator* (T_FLOAT v) const
{
  Quaternion ret = *this;
  ret.v *= v;
  ret.w *= v;
  return ret;
}
GG_INLINE const Quaternion Quaternion::operator* (const Quaternion& other) const
{
  Quaternion ret = Quaternion();
  ret.v = TVec3f::Cross(this->v, other.v) + this->v * other.w + other.v * this->w;
  ret.w = this->w * other.w - TVec3f::Dot(this->v, other.v);
  return ret;
}
GG_INLINE Quaternion& Quaternion::operator*= (T_FLOAT v)
{
  return *this = *this * v;
}
GG_INLINE Quaternion& Quaternion::operator*= (const Quaternion& other)
{
  return *this = *this * other;
}

// œŽZ
GG_INLINE const Quaternion Quaternion::operator/ (T_FLOAT s) const
{
  Quaternion ret = *this;
  ret.v /= s;
  ret.w /= s;
  return ret;
}
//GG_INLINE const Quaternion Quaternion::operator/ (const Quaternion& other) const
//{
//  return Quaternion(this->eigen * other.eigen.conjugate());
//}
//GG_INLINE Quaternion& Quaternion::operator/= (T_FLOAT s)
//{
//  this->eigen *= other.eigen.conjugate();
//  return *this;
//}
//GG_INLINE Quaternion& Quaternion::operator/= (const Quaternion& other)
//{
//  this->eigen *= other.eigen.conjugate();
//  return *this;
//}

// ”äŠr
GG_INLINE bool Quaternion::operator== (const Quaternion& other) const
{
  return
    (this->v == other.v && this->w == other.w) ||
    (this->v == -other.v && this->w == -other.w)
    ;
}
GG_INLINE bool Quaternion::operator!= (const Quaternion& other) const
{
  return
    (this->v == other.v && this->w == other.w) ||
    (this->v == -other.v && this->w == -other.w)
    ;
}
