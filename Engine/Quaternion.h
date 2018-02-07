#pragma once

#include "Geometry.h"
#include "NativeMatrix.h"

struct Quaternion
{
  // =================================================================
  // Static Member
  // =================================================================
public:
  static const Quaternion Identity;
  static const Quaternion Eular(const TVec3f& eular_angles);
  static const Quaternion Lerp(const Quaternion a, const Quaternion b, T_FLOAT t);
  static const Quaternion Slerp(const Quaternion a, const Quaternion b, T_FLOAT t);
  static const Quaternion LookRotation(const TVec3f& forward, const TVec3f& upwards = TVec3f(0.0f, 1.0f, 0.0f));

  static T_FLOAT InnerProduct(const Quaternion& a, const Quaternion& b);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
  Quaternion();
  Quaternion(const TVec3f& v, T_FLOAT rad);
  Quaternion(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT w);

  // =================================================================
  // Operator
  // =================================================================
  bool operator == (const Quaternion& other) const
  {
    return
      (this->v_ == other.v_ && this->w_ == other.w_) ||
      (this->v_ == -other.v_ && this->w_ == -other.w_)
      ;
  }

  const Quaternion operator - () const
  {
    Quaternion ret = *this;
    ret.v_ = -ret.v_;
    ret.w_ = -ret.w_;
    return ret;
  }

  const Quaternion operator * (T_FLOAT v) const
  {
    Quaternion ret = *this;
    ret.v_ *= v;
    ret.w_ *= v;
    return ret;
  }

  const Quaternion operator + (const Quaternion& other) const
  {
    Quaternion ret = *this;
    ret.v_ += other.v_;
    ret.w_ += other.w_;
    return ret;
  }

  const Quaternion operator * (const Quaternion& other) const
  {
    Quaternion ret = Quaternion();
    ret.v_ = TVec3f::OuterProduct(this->v_, other.v_) + this->v_ * other.w_ + other.v_ * this->w_;
    ret.w_ = this->w_ * other.w_ - TVec3f::InnerProduct(this->v_, other.v_);
    return ret;
  }

  const Quaternion operator / (T_FLOAT s) const
  {
    Quaternion ret = Quaternion();
    ret.v_ = this->v_ / s;
    ret.w_ = this->w_ / s;
    return ret;
  }

  // =================================================================
  // Methods
  // =================================================================
  void q(const TVec3f& v, T_FLOAT rad);

  void FromEularAngles(const TVec3f& mat);
  void FromRotationMatrix(const INativeMatrix& mat);
  void ToRotationMatrix(INativeMatrix* dest);

  T_FLOAT ScalarSquare() const;
  T_FLOAT Scalar() const;
  const Quaternion Conjugated() const;
  const Quaternion Inversed() const;
  const Quaternion Normalized() const;
  bool IsNormal(T_FLOAT eps = 0.1f) const;

  // =================================================================
  // Data Members
  // =================================================================
  TVec3f v_;
  T_FLOAT w_;
};