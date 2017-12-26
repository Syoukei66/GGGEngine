#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <NativeMatrix.h>

class NativeMatrix : public INativeMatrix
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeMatrix();
  NativeMatrix(NativeMatrixInstance* instance);
  ~NativeMatrix();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Init() override;
  virtual void Assign(NativeMatrixInstance* mat) override;
  virtual void Assign(const INativeMatrix& mat) override;
  virtual void Multiple(const INativeMatrix& mat) override;
  virtual void Inverse() override;
  virtual void Inverse(INativeMatrix* dest) const override;

  virtual void Translation(T_FLOAT x, T_FLOAT y) override;
  virtual void Translation(const TVec2f& value) override;
  virtual void Translation(T_FLOAT x, T_FLOAT y, T_FLOAT z) override;
  virtual void Translation(const TVec3f& value) override;
  virtual void TranslationX(T_FLOAT x) override;
  virtual void TranslationY(T_FLOAT y) override;
  virtual void TranslationZ(T_FLOAT z) override;

  virtual void Scaling(T_FLOAT value) override;
  virtual void Scaling(T_FLOAT x, T_FLOAT y) override;
  virtual void Scaling(const TVec2f& value) override;
  virtual void Scaling(T_FLOAT x, T_FLOAT y, T_FLOAT z) override;
  virtual void Scaling(const TVec3f& value) override;
  virtual void ScalingX(T_FLOAT x) override;
  virtual void ScalingY(T_FLOAT y) override;
  virtual void ScalingZ(T_FLOAT z) override;

  virtual void Rotation(T_FLOAT x, T_FLOAT y) override;
  virtual void Rotation(const TVec2f& value) override;
  virtual void Rotation(T_FLOAT x, T_FLOAT y, T_FLOAT z) override;
  virtual void Rotation(const TVec3f& value) override;
  virtual void RotationX(T_FLOAT x) override;
  virtual void RotationY(T_FLOAT y) override;
  virtual void RotationZ(T_FLOAT z) override;

  virtual void Apply(TVec2f* dest) const override;
  virtual void Apply(TVec3f* dest) const override;
  virtual void Apply(TVec4f* dest) const override;
  virtual void Apply(T_FLOAT* dest_x, T_FLOAT* dest_y) const override;
  virtual void Apply(T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z) const override;
  virtual void Apply(T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z, T_FLOAT* dest_w) const override;

  virtual void Direction(TVec2f* dest) const override;
  virtual void Direction(TVec3f* dest) const override;

  virtual void LookAtLH(const TVec3f& camera_pos, const TVec3f& camera_at, const TVec3f& camera_up) override;
  virtual void PerspectiveFovLH(T_FLOAT field_of_view_y, T_FLOAT aspect_ratio, T_FLOAT z_near, T_FLOAT z_far) override;
  virtual void OrthoLH(T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far) override;
  
protected:
  virtual const T_FLOAT* Get(T_UINT8 x) const override;
  virtual T_FLOAT* Get(T_UINT8 x) override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  D3DXMATRIX* mat_;

};