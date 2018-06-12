#pragma once

#include "Eigen\Core"
#include "Eigen\Geometry"

#include "NativeMatrix.h"
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
    : eigen(rad, v.x, v.y, v.z)
  {}
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
    Quaternion ret = Quaternion();
    const T_FLOAT sin_ = sinf(0.0f);
    const T_FLOAT cos_ = cosf(0.0f);
    ret.v_ = eular_angles.Normalized() * sin_;
    ret.w_ = cos_;
    float cosY = cosf(eular_angles.y / 2.0f);
    float sinY = sinf(eular_angles.y / 2.0f);
    float cosP = cosf(eular_angles.x / 2.0f);
    float sinP = sinf(eular_angles.x / 2.0f);
    float cosR = cosf(eular_angles.z / 2.0f);
    float sinR = sinf(eular_angles.z / 2.0f);
    ret.v_.x = cosR * sinP * cosY + sinR * cosP * sinY;
    ret.v_.y = cosR * cosP * sinY - sinR * sinP * cosY;
    ret.v_.z = sinR * cosP * cosY - cosR * sinP * sinY;
    ret.w_ = cosR * cosP * cosY + sinR * sinP * sinY;
    return ret;
  }
  //static const Quaternion Lerp(const Quaternion a, const Quaternion b, T_FLOAT t)
  //{
  //  return a + (b - a) * t;
  //}
  static const Quaternion Lerp(const Quaternion a, const Quaternion b, T_FLOAT t);
  static inline const Quaternion Slerp(const Quaternion a, const Quaternion b, T_FLOAT t)
  {
    return Quaternion(a.eigen.slerp(t, b.eigen));
  }
  static const Quaternion LookRotation(const TVec3f& forward, const TVec3f& upwards = TVec3f(0.0f, 1.0f, 0.0f));

  static inline T_FLOAT InnerProduct(const Quaternion& a, const Quaternion& b)
  {
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
    Quaternion ret = Quaternion();
    ret.v_ = TVec3f::OuterProduct(this->v_, other.v_) + this->v_ * other.w_ + other.v_ * this->w_;
    ret.w_ = this->w_ * other.w_ - TVec3f::InnerProduct(this->v_, other.v_);
    return ret;
    //return Quaternion(this->eigen * other.eigen);
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
  void FromRotationMatrix(const INativeMatrix& mat);
  void ToRotationMatrix(INativeMatrix* dest);

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