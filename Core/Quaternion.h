#pragma once

#include <Eigen/Core.h>
#include <Eigen/Geometry.h>

#include "Matrix4x4.h"
#include "Vector3.h"

union Quaternion
{
  // =================================================================
  // Constants
  // =================================================================
public:
  static const Quaternion Identity;

  // =================================================================
  // Data Members
  // =================================================================
public:
  struct
  {
    TVec3f v_;
    T_FLOAT w_;
  };
  T_FLOAT val[4];
  Eigen::Quaternionf eigen;

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
    this->v_ = v.Normalized() * sin_;
    this->w_ = cos_;
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
  inline operator Eigen::Quaternionf() const
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
  static inline const Quaternion Lerp(const Quaternion& a, const Quaternion& b, T_FLOAT t)
  {
    if (t <= 0.0f)
    {
      return a;
    }
    if (t >= 1.0f)
    {
      return b;
    }
    const T_FLOAT r = acosf(InnerProduct(a, b));
    if (fabs(r) <= Mathf::PI_1_2)
    {
      return (a + (b - a) * t).Normalized();
    }
    return (a + (b - a) * -t).Normalized();
  }
  static inline const Quaternion Slerp(const Quaternion& a, const Quaternion& b, T_FLOAT t)
  {
    if (t <= 0.0f)
    {
      return a;
    }
    if (t >= 1.0f)
    {
      return b;
    }
    const T_FLOAT r = acosf(InnerProduct(a, b));
    if (fabs(r) <= Mathf::PI_1_2)
    {
      return Quaternion(a.eigen.slerp(t, b.eigen));
    }
    return Quaternion(a.eigen.slerp(-t, b.eigen));
  }
  static const Quaternion LookRotation(const TVec3f& forward, const TVec3f& upwards = TVec3f(0.0f, 1.0f, 0.0f));

  static inline T_FLOAT InnerProduct(const Quaternion& a, const Quaternion& b)
  {
    //return a.v_.x * b.v_.x + a.v_.y * b.v_.y + a.v_.z * b.v_.z + a.w_ * b.w_;
    //return TVec3f::InnerProduct(a.v_, b.v_) + a.w_ * b.w_;
    return a.eigen.dot(b.eigen);
  }

  // =================================================================
  // Operator
  // =================================================================
public:
  //+
  inline const Quaternion operator + () const
  {
    return *this;
  }
  //-
  inline const Quaternion operator - () const
  {
    Quaternion ret = *this;
    ret.v_ = -ret.v_;
    ret.w_ = -ret.w_;
    return ret;
  }
  //‚Q€+
  inline const Quaternion operator + (const Quaternion& other) const
  {
    Quaternion ret = *this;
    ret.v_ += other.v_;
    ret.w_ += other.w_;
    return ret;
  }
  inline Quaternion& operator += (const Quaternion& other)
  {
    this->v_ += other.v_;
    this->w_ += other.w_;
    return *this;
  }
  //‚Q€-
  inline const Quaternion operator - (const Quaternion& other) const
  {
    Quaternion ret = *this;
    ret.v_ -= other.v_;
    ret.w_ -= other.w_;
    return ret;
  }
  inline Quaternion& operator -= (const Quaternion& other)
  {
    this->v_ -= other.v_;
    this->w_ -= other.w_;
    return *this;
  }
  //‚Q€*
  inline const Quaternion operator * (T_FLOAT v) const
  {
    Quaternion ret = *this;
    ret.v_ *= v;
    ret.w_ *= v;
    return ret;
  }
  inline const Quaternion operator * (const Quaternion& other) const
  {
    return Quaternion(this->eigen * other.eigen);
  }
  inline Quaternion& operator *= (const Quaternion& other)
  {
    this->eigen *= other.eigen;
    return *this;
  }
  //‚Q€/
  inline const Quaternion operator / (T_FLOAT s) const
  {
    Quaternion ret = *this;
    ret.v_ /= s;
    ret.w_ /= s;
    return ret;
  }
  inline const Quaternion operator / (const Quaternion& other) const
  {
    return Quaternion(this->eigen * other.eigen.conjugate());
  }
  inline Quaternion& operator /= (const Quaternion& other)
  {
    this->eigen *= other.eigen.conjugate();
    return *this;
  }
  //‚Q€==
  bool operator == (const Quaternion& other) const
  {
    return
      (this->v_ == other.v_ && this->w_ == other.w_) ||
      (this->v_ == -other.v_ && this->w_ == -other.w_)
      ;
  }
  // =================================================================
  // Methods
  // =================================================================

  //TODO: Matrix‘¤‚ÉˆÚ“®‚·‚é‚×‚«‚©
  void FromRotationMatrix(const Matrix4x4& mat);
  void ToRotationMatrix(Matrix4x4* dest);

  inline T_FLOAT ScalarSquare() const
  {
    return this->eigen.squaredNorm();
  }
  inline T_FLOAT Scalar() const
  {
    return this->eigen.norm();
  }
  inline const Quaternion Conjugated() const
  {
    return Quaternion(this->eigen.conjugate());
  }
  inline const Quaternion Inversed() const
  {
    return Quaternion(this->eigen.inverse());
  }
  inline const Quaternion Normalized() const
  {
    return Quaternion(this->eigen.normalized());
  }
  inline bool IsNormal(T_FLOAT eps = 0.1f) const
  {
    return fabs(1.0f - this->eigen.squaredNorm()) < eps;
  }

};