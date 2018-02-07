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
  NativeMatrix(const NativeMatrix& mat);
  ~NativeMatrix();

  // =================================================================
  // Method
  // =================================================================
public:
  void Init() override;
  void Assign(NativeMatrixInstance* mat) override;
  void Assign(const INativeMatrix& mat) override;
  void Multiple(const INativeMatrix& mat) override;
  void MultipleReverse(const INativeMatrix& mat) override;
  void Inverse() override;
  void Inverse(INativeMatrix* dest) const override;

  void Translation(T_FLOAT x, T_FLOAT y) override;
  void Translation(const TVec2f& value) override;
  void Translation(T_FLOAT x, T_FLOAT y, T_FLOAT z) override;
  void Translation(const TVec3f& value) override;
  void TranslationX(T_FLOAT x) override;
  void TranslationY(T_FLOAT y) override;
  void TranslationZ(T_FLOAT z) override;

  void Scaling(T_FLOAT value) override;
  void Scaling(T_FLOAT x, T_FLOAT y) override;
  void Scaling(const TVec2f& value) override;
  void Scaling(T_FLOAT x, T_FLOAT y, T_FLOAT z) override;
  void Scaling(const TVec3f& value) override;
  void ScalingX(T_FLOAT x) override;
  void ScalingY(T_FLOAT y) override;
  void ScalingZ(T_FLOAT z) override;

  void Rotation(T_FLOAT x, T_FLOAT y) override;
  void Rotation(const TVec2f& value) override;
  void Rotation(T_FLOAT x, T_FLOAT y, T_FLOAT z) override;
  void Rotation(const TVec3f& value) override;
  void RotationX(T_FLOAT x) override;
  void RotationY(T_FLOAT y) override;
  void RotationZ(T_FLOAT z) override;

  void LookAtLH(const TVec3f& camera_pos, const TVec3f& camera_at, const TVec3f& camera_up) override;
  void PerspectiveFovLH(T_FLOAT field_of_view_y, T_FLOAT aspect_ratio, T_FLOAT z_near, T_FLOAT z_far) override;
  void OrthoLH(T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far) override;

  void Apply(TVec2f* dest) const override;
  void Apply(TVec3f* dest) const override;
  void Apply(TVec4f* dest) const override;
  void Apply(T_FLOAT* dest_x, T_FLOAT* dest_y) const override;
  void Apply(T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z) const override;
  void Apply(T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z, T_FLOAT* dest_w) const override;

  const TVec2f GetDirection2d() const override;
  const TVec3f GetDirection3d() const override;
  const TVec2f GetPosition2d() const override;
  const TVec3f GetPosition3d() const override;
  const TVec4f GetPosition4d() const override;

  const TVec3f GetCameraXVec() const override;
  const TVec3f GetCameraYVec() const override;
  const TVec3f GetCameraZVec() const override;

  const TVec3f GetWorldScale() const override;

protected:
  const T_FLOAT* Get(T_UINT8 x) const override;
  T_FLOAT* Get(T_UINT8 x) override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  D3DXMATRIX* mat_;
  
};