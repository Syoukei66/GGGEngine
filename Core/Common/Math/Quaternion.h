#pragma once

#include <Eigen/Core.h>
#include <Eigen/Geometry.h>

#include "Matrix4x4.h"
#include "Vector3.h"

struct Quaternion
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(Quaternion)
  {
    archive(v);
    archive(w);
  }

  // =================================================================
  // Constants
  // =================================================================
public:
  static const Quaternion Identity;

  // =================================================================
  // Data Members
  // =================================================================
public:
  union
  {
    struct
    {
      TVec3f v;
      T_FLOAT w;
    };
    T_FLOAT val[4];
    Eigen::Quaternionf eigen;
  };

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Quaternion()
    : eigen(1.0f, 0.0f, 0.0f, 0.0f)
  {}
  Quaternion(const Eigen::Quaternionf& eigen)
    : eigen(eigen)
  {}
  Quaternion(const TVec3f& v, T_FLOAT rad)
  {
    const T_FLOAT sin_ = sinf(rad / 2.0f);
    const T_FLOAT cos_ = cosf(rad / 2.0f);
    this->v = v.Normalized() * sin_;
    this->w = cos_;
  }
  Quaternion(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT w)
    : eigen(w, x, y, z)
  {}

  // =================================================================
  // Copy Constructor / Assign operator
  // =================================================================
public:
  Quaternion(const Quaternion& q)
    : eigen(q.eigen)
  {}

  Quaternion& operator=(const Quaternion& other)
  {
    this->eigen = other.eigen;
    return *this;
  }

  // =================================================================
  // Cast Operator
  // =================================================================
public:
  GG_INLINE operator Eigen::Quaternionf() const
  {
    return this->eigen;
  }

  // =================================================================
  // Static Methods
  // =================================================================
public:
  static const Quaternion Eular(const TVec3f& eular_angles)
  {
    using namespace Eigen;
    Quaternionf q = AngleAxisf(eular_angles.z, Vector3f::UnitZ())
    * AngleAxisf(eular_angles.x, Vector3f::UnitX())
    * AngleAxisf(eular_angles.y, Vector3f::UnitY());
    return q;
  }
  //static const Quaternion Lerp(const Quaternion a, const Quaternion b, T_FLOAT t)
  //{
  //  return a + (b - a) * t;
  //}
  static GG_INLINE const Quaternion Lerp(const Quaternion& a, const Quaternion& b, T_FLOAT t)
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
  static GG_INLINE const Quaternion Slerp(const Quaternion& a, const Quaternion& b, T_FLOAT t)
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
      return Quaternion(a.eigen.slerp(t, b.eigen));
    }
    return Quaternion(a.eigen.slerp(-t, b.eigen));
  }
  static const Quaternion LookRotation(const TVec3f& forward, const TVec3f& upwards = TVec3f(0.0f, 1.0f, 0.0f));

  static GG_INLINE T_FLOAT Dot(const Quaternion& a, const Quaternion& b)
  {
    //return a.v.x * b.v.x + a.v.y * b.v.y + a.v.z * b.v.z + a.w * b.w;
    //return TVec3f::Dot(a.v, b.v) + a.w * b.w;
    return a.eigen.dot(b.eigen);
  }

  // =================================================================
  // Operator
  // =================================================================
public:
  //+
  GG_INLINE const Quaternion operator + () const
  {
    return *this;
  }
  //-
  GG_INLINE const Quaternion operator - () const
  {
    Quaternion ret = *this;
    ret.v = -ret.v;
    ret.w = -ret.w;
    return ret;
  }
  //‚Q€+
  GG_INLINE const Quaternion operator + (const Quaternion& other) const
  {
    Quaternion ret = *this;
    ret.v += other.v;
    ret.w += other.w;
    return ret;
  }
  GG_INLINE Quaternion& operator += (const Quaternion& other)
  {
    this->v += other.v;
    this->w += other.w;
    return *this;
  }
  //‚Q€-
  GG_INLINE const Quaternion operator - (const Quaternion& other) const
  {
    Quaternion ret = *this;
    ret.v -= other.v;
    ret.w -= other.w;
    return ret;
  }
  GG_INLINE Quaternion& operator -= (const Quaternion& other)
  {
    this->v -= other.v;
    this->w -= other.w;
    return *this;
  }
  //‚Q€*
  GG_INLINE const Quaternion operator * (T_FLOAT v) const
  {
    Quaternion ret = *this;
    ret.v *= v;
    ret.w *= v;
    return ret;
  }
  GG_INLINE const Quaternion operator * (const Quaternion& other) const
  {
    return Quaternion(this->eigen * other.eigen);
  }
  GG_INLINE Quaternion& operator *= (const Quaternion& other)
  {
    this->eigen *= other.eigen;
    return *this;
  }
  //‚Q€/
  GG_INLINE const Quaternion operator / (T_FLOAT s) const
  {
    Quaternion ret = *this;
    ret.v /= s;
    ret.w /= s;
    return ret;
  }
  GG_INLINE const Quaternion operator / (const Quaternion& other) const
  {
    return Quaternion(this->eigen * other.eigen.conjugate());
  }
  GG_INLINE Quaternion& operator /= (const Quaternion& other)
  {
    this->eigen *= other.eigen.conjugate();
    return *this;
  }
  //‚Q€==
  bool operator == (const Quaternion& other) const
  {
    return
      (this->v == other.v && this->w == other.w) ||
      (this->v == -other.v && this->w == -other.w)
      ;
  }
  // =================================================================
  // Methods
  // =================================================================

  //TODO: Matrix‘¤‚ÉˆÚ“®‚·‚é‚×‚«‚©
  void FromRotationMatrix(const Matrix4x4& mat);
  void ToRotationMatrix(Matrix4x4* dest);

  GG_INLINE T_FLOAT ScalarSquare() const
  {
    return this->eigen.squaredNorm();
  }
  GG_INLINE T_FLOAT Scalar() const
  {
    return this->eigen.norm();
  }
  GG_INLINE const Quaternion Conjugated() const
  {
    return Quaternion(this->eigen.conjugate());
  }
  GG_INLINE const Quaternion Inversed() const
  {
    return Quaternion(this->eigen.inverse());
  }
  GG_INLINE const Quaternion Normalized() const
  {
    return Quaternion(this->eigen.normalized());
  }
  GG_INLINE bool IsNormal(T_FLOAT eps = 0.1f) const
  {
    return fabs(1.0f - this->eigen.squaredNorm()) < eps;
  }

};