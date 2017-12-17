#pragma once

#include "Geometry.h"

class Quaternion
{
  // =================================================================
  // Static Member
  // =================================================================
public:
  static const Quaternion Identity;

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Quaternion();
  ~Quaternion();

  // =================================================================
  // Operator
  // =================================================================
public:
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
  // Method
  // =================================================================
public:
  void RotationXAxis(T_FLOAT rad);
  void RotationYAxis(T_FLOAT rad);
  void RotationZAxis(T_FLOAT rad);

  void RotationX(const TVec3f& direction, T_FLOAT rad);
  void RotationY(const TVec3f& direction, T_FLOAT rad);
  void RotationZ(const TVec3f& direction, T_FLOAT rad);

  const TVec3f& EularAngles();

  void SetRotationWithAxis(const TVec3f& rotation);
  void SetRotationWithAxis(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  void SetRotationWithMatrix(LP_MATRIX_4x4 matrix);

  const void q(const TVec3f& v, T_FLOAT rad);

private:
  //static T_FLOAT ScalarSquare(const Quaternion& q);
  //static T_FLOAT Scalar(const Quaternion& q);
  //static const Quaternion Conjugated(const Quaternion& q);
  //static const Quaternion Inversed(const Quaternion& q);
  //static const Quaternion Normalized(const Quaternion& q);

  //Matrix‚É‡‚í‚¹‚ÄQuaternion‚Ì’l‚ð•Ï‰»‚³‚¹‚é
  void FromRotationMatrix();

  //Quaternion‚Ì’l‚É‡‚í‚¹‚ÄMatrix‚ðì¬
  void PrepareRotationMatrix();

  //Quaternion‚Ì’l‚É‡‚í‚¹‚ÄEularAngles‚ðì¬
  void PrepareEularAngles();

public:
  inline LP_MATRIX_4x4 GetMatrix()
  {
    this->PrepareRotationMatrix();
    return this->rotation_matrix_;
  }

  inline const TVec3f& GetEularAngles()
  {
    return this->eular_angles_;
  }

  inline T_FLOAT GetEularX()
  {
    this->PrepareEularAngles();
    return this->eular_angles_.x;
  }

  inline T_FLOAT GetEularY()
  {
    this->PrepareEularAngles();
    return this->eular_angles_.y;
  }

  inline T_FLOAT GetEularZ()
  {
    this->PrepareEularAngles();
    return this->eular_angles_.z;
  }

  // =================================================================
  // setter/getter
  // =================================================================
private:
  LP_MATRIX_4x4 rotation_matrix_;
  TVec3f v_;
  T_FLOAT w_;
  TVec3f eular_angles_;
  bool need_rotation_matrix_update_;
  bool need_eular_angles_update_;
};