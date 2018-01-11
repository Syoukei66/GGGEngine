#pragma once

#include "Geometry.h"
#include "Quaternion.h"

class Transform3D;

class Transform3DRotator
{

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
  void RotateX(T_FLOAT rad);
  void RotateY(T_FLOAT rad);
  void RotateZ(T_FLOAT rad);

  void RotateXAxis(T_FLOAT rad);
  void RotateYAxis(T_FLOAT rad);
  void RotateZAxis(T_FLOAT rad);

  void FromRotationMatrix(INativeMatrix* matrix);
  void ToRotationMatrix(INativeMatrix* dest);

  const void q(const TVec3f& v, T_FLOAT rad);

private:

  //Matrix‚É‡‚í‚¹‚ÄTransform3DRotator‚Ì’l‚ð•Ï‰»‚³‚¹‚é
  void FromRotationMatrix();

  //Transform3DRotator‚Ì’l‚É‡‚í‚¹‚ÄMatrix‚ðì¬
  void PrepareRotationMatrix();

  //Transform3DRotator‚Ì’l‚É‡‚í‚¹‚ÄEularAngles‚ðì¬
  void PrepareEularAngles();


  // =================================================================
  // setter/getter
  // =================================================================
public:
  void SetEularAngles(const TVec3f& rotation);
  void SetEularAngles(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  inline const TVec3f& GetEularAngles()
  {
    this->PrepareEularAngles();
    return this->eular_angles_;
  }

  void SetEularX(T_FLOAT x);
  inline T_FLOAT GetEularX()
  {
    this->PrepareEularAngles();
    return this->eular_angles_.x;
  }

  void SetEularY(T_FLOAT y);
  inline T_FLOAT GetEularY()
  {
    this->PrepareEularAngles();
    return this->eular_angles_.y;
  }

  void SetEularZ(T_FLOAT z);
  inline T_FLOAT GetEularZ()
  {
    this->PrepareEularAngles();
    return this->eular_angles_.z;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Transform3D* transform_;
  INativeMatrix* rotation_matrix_;
  Quaternion quaternion_;
  TVec3f eular_angles_;
  bool need_rotation_matrix_update_;
  bool need_eular_angles_update_;
};