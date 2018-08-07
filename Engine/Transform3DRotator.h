#pragma once

#include "../Common/Vector3.h"
#include "../Common/Quaternion.h"

class Transform3D;

class Transform3DRotator
{
private:
  enum
  {
    MASTER_QUATERNION = 1 << 0,
    MASTER_EULAR      = 1 << 1,
    MASTER_MATRIX     = 1 << 2,
  };

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Transform3DRotator(Transform3D* transform);
  ~Transform3DRotator();
  
  // =================================================================
  // Methods
  // =================================================================
public:
  void Init();

  void RotateX(T_FLOAT rad);
  void RotateY(T_FLOAT rad);
  void RotateZ(T_FLOAT rad);
  void Rotate(const TVec3f& v, T_FLOAT rad);

  void FromRotationMatrix(const Matrix4x4& matrix);
  void ToRotationMatrix(Matrix4x4* dest);

  void Lerp(const Quaternion& a, const Quaternion& b, T_FLOAT t);
  void Lerp(const Quaternion& b, T_FLOAT t);
  void Slerp(const Quaternion& a, const Quaternion& b, T_FLOAT t);
  void Slerp(const Quaternion& b, T_FLOAT t);

private:
  void PrepareQuaternion();
  void PrepareRotationMatrix();
  void PrepareEularAngles();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  void SetEularAngles(const TVec3f& rotation);
  void SetEularAngles(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  inline const TVec3f& GetEularAngles() const
  {
    const_cast<Transform3DRotator*>(this)->PrepareEularAngles();
    return this->eular_angles_;
  }

  void SetEularX(T_FLOAT x);
  inline T_FLOAT GetEularX() const
  {
    const_cast<Transform3DRotator*>(this)->PrepareEularAngles();
    return this->eular_angles_.x;
  }

  void SetEularY(T_FLOAT y);
  inline T_FLOAT GetEularY() const
  {
    const_cast<Transform3DRotator*>(this)->PrepareEularAngles();
    return this->eular_angles_.y;
  }

  void SetEularZ(T_FLOAT z);
  inline T_FLOAT GetEularZ() const
  {
    const_cast<Transform3DRotator*>(this)->PrepareEularAngles();
    return this->eular_angles_.z;
  }

  inline const Quaternion& GetQuaternion() const
  {
    const_cast<Transform3DRotator*>(this)->PrepareQuaternion();
    return this->quaternion_;
  }

  inline const Matrix4x4& GetRotationMatrix() const
  {
    const_cast<Transform3DRotator*>(this)->PrepareRotationMatrix();
    return this->rotation_matrix_;
  }
  // =================================================================
  // Data Member
  // =================================================================
private:
  Transform3D* transform_;
  Matrix4x4 rotation_matrix_;
  Quaternion quaternion_;
  TVec3f eular_angles_;
  T_UINT32 master_flag_;
};