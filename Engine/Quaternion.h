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
  static Quaternion Eular(const TVec3f& eular_angles);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
  Quaternion();
  Quaternion(const TVec3f& v, T_FLOAT rad);

  // =================================================================
  // Operator
  // =================================================================
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

  // =================================================================
  // Data Members
  // =================================================================
  TVec3f v_;
  T_FLOAT w_;
};