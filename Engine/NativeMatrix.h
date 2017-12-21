#pragma once

#include "Geometry.h"

class INativeMatrix
{
  // =================================================================
  // Static Method
  // =================================================================
public:
  static const INativeMatrix& Identity();

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  INativeMatrix() {}
  virtual ~INativeMatrix() {}

private:
  INativeMatrix(const INativeMatrix& mat) {}

  // =================================================================
  // Operator
  // =================================================================
public:
  //乗算などを定義しない理由は、
  //暗黙的にNativeMatrixのインスタンスが生成されてしまうのを防ぐため

  inline INativeMatrix& operator = (const INativeMatrix& mat)
  {
    this->Assign(mat);
    return (*this);
  }
  inline INativeMatrix& operator *= (const INativeMatrix& mat)
  {
    this->Multiple(mat);
    return (*this);
  }
  inline const T_FLOAT* operator [] (T_UINT8 x) const
  {
    return this->Get(x);
  }
  inline T_FLOAT* operator [] (T_UINT8 x)
  {
    return this->Get(x);
  }

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Init() = 0;

  virtual void Assign(const INativeMatrix& mat) = 0;
  virtual void Multiple(const INativeMatrix& mat) = 0;

  virtual void Translation(T_FLOAT x, T_FLOAT y) = 0;
  virtual void Translation(const TVec2f& value) = 0;
  virtual void Translation(T_FLOAT x, T_FLOAT y, T_FLOAT z) = 0;
  virtual void Translation(const TVec3f& value) = 0;
  virtual void TranslationX(T_FLOAT x) = 0;
  virtual void TranslationY(T_FLOAT y) = 0;
  virtual void TranslationZ(T_FLOAT z) = 0;

  virtual void Scaling(T_FLOAT value) = 0;
  virtual void Scaling(T_FLOAT x, T_FLOAT y) = 0;
  virtual void Scaling(const TVec2f& value) = 0;
  virtual void Scaling(T_FLOAT x, T_FLOAT y, T_FLOAT z) = 0;
  virtual void Scaling(const TVec3f& value) = 0;
  virtual void ScalingX(T_FLOAT x) = 0;
  virtual void ScalingY(T_FLOAT y) = 0;
  virtual void ScalingZ(T_FLOAT z) = 0;

  virtual void Rotation(T_FLOAT x, T_FLOAT y) = 0;
  virtual void Rotation(const TVec2f& value) = 0;
  virtual void Rotation(T_FLOAT x, T_FLOAT y, T_FLOAT z) = 0;
  virtual void Rotation(const TVec3f& value) = 0;
  virtual void RotationX(T_FLOAT x) = 0;
  virtual void RotationY(T_FLOAT y) = 0;
  virtual void RotationZ(T_FLOAT z) = 0;

  virtual void Apply(TVec2f* dest) const = 0;
  virtual void Apply(TVec3f* dest) const = 0;
  virtual void Apply(TVec4f* dest) const = 0;
  virtual void Apply(T_FLOAT* dest_x, T_FLOAT* dest_y) const = 0;
  virtual void Apply(T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z) const = 0;
  virtual void Apply(T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z, T_FLOAT* dest_w) const = 0;

  virtual void Direction(TVec2f* dest) const = 0;
  virtual void Direction(TVec3f* dest) const = 0;

  virtual void LookAtLH(const TVec3f& camera_pos, const TVec3f& camera_at, const TVec3f& camera_up) = 0;
  virtual void PerspectiveFovLH(T_FLOAT field_of_view_y, T_FLOAT aspect_ratio, T_FLOAT z_near, T_FLOAT z_far) = 0;
  virtual void OrthoLH(T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far) = 0;

protected:
  virtual const T_FLOAT* Get(T_UINT8 x) const = 0;
  virtual T_FLOAT* Get(T_UINT8 x) = 0;

};
