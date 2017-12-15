#ifndef HAL_DIRECTX_ACTIVITY_NATIVE_NATIVEPROCESS_MATRIX_H_
#define HAL_DIRECTX_ACTIVITY_NATIVE_NATIVEPROCESS_MATRIX_H_

#include "../../Engine/INativeProcess_Matrix.h"

class NativeProcess_Matrix : public INativeProcess_Matrix
{
public:
  virtual LP_MATRIX_4x4 Matrix4x4_GetIdentity() const override;

  virtual LP_MATRIX_4x4 Matrix4x4_Create() const override;
  virtual void Matrix4x4_Init(LP_MATRIX_4x4 matrix) const override;
  virtual void Matrix4x4_Delete(LP_MATRIX_4x4 matrix) const override;
  virtual void Matrix4x4_Assign(LP_MATRIX_4x4 dst, LP_MATRIX_4x4 mat) const override;

  virtual void Matrix4x4_Inverse(LP_MATRIX_4x4 dst, LP_MATRIX_4x4 mat) const override;
  virtual void Matrix4x4_Multiply(LP_MATRIX_4x4 dst, LP_MATRIX_4x4 mat) const override;

  virtual void Matrix4x4_Translate(LP_MATRIX_4x4 mat, T_FLOAT x, T_FLOAT y, T_FLOAT z) const override;
  virtual void Matrix4x4_Scaling(LP_MATRIX_4x4 mat, T_FLOAT x, T_FLOAT y, T_FLOAT z) const override;
  virtual void Matrix4x4_Rotation(LP_MATRIX_4x4 mat, T_FLOAT x, T_FLOAT y, T_FLOAT z) const override;

  virtual void Matrix4x4_Apply(LP_MATRIX_4x4 mat, TVec2f* dest) const override;
  virtual void Matrix4x4_Apply(LP_MATRIX_4x4 mat, TVec3f* dest) const override;
  virtual void Matrix4x4_Apply(LP_MATRIX_4x4 mat, TVec4f* dest) const override;
  virtual void Matrix4x4_Apply(LP_MATRIX_4x4 mat, T_FLOAT* dest_x, T_FLOAT* dest_y) const override;
  virtual void Matrix4x4_Apply(LP_MATRIX_4x4 mat, T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z) const override;
  virtual void Matrix4x4_Apply(LP_MATRIX_4x4 mat, T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z, T_FLOAT* dest_w) const override;

  virtual void Matrix4x4_Set(LP_MATRIX_4x4 mat, T_UINT8 x, T_UINT8 y, T_FLOAT value) const override;
  virtual T_FLOAT Matrix4x4_Get(LP_MATRIX_4x4 mat, T_UINT8 x, T_UINT8 y) const override;

  virtual void Matrix4x4_Direction(LP_MATRIX_4x4 mat, TVec3f* dest) const override;

  virtual void Matrix4x4_LookAtLH(LP_MATRIX_4x4 mat, const TVec3f& camera_pos, const TVec3f& camera_at, const TVec3f& camera_up) const override;
  virtual void Matrix4x4_PerspectiveFovLH(LP_MATRIX_4x4 mat, T_FLOAT field_of_view_y, T_FLOAT aspect_ratio, T_FLOAT z_near, T_FLOAT z_far) const override;
  virtual void Matrix4x4_OrthoLH(LP_MATRIX_4x4 mat, T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far) const override;

  virtual LP_MATRIX_4x4_STACK Matrix4x4Stack_Create() const override;
  virtual void Matrix4x4Stack_Push(LP_MATRIX_4x4_STACK stack, LP_MATRIX_4x4 matrix) const override;
  virtual void Matrix4x4Stack_Pop(LP_MATRIX_4x4_STACK stack) const override;
  virtual void Matrix4x4Stack_Delete(LP_MATRIX_4x4_STACK stack) const override;
  virtual void Matrix4x4Stack_Apply(LP_DEVICE device, LP_MATRIX_4x4_STACK stack) const override;
  virtual LP_MATRIX_4x4 Matrix4x4Stack_GetTop(LP_MATRIX_4x4_STACK stack) const override;

};

#endif//HAL_DIRECTX_ACTIVITY_NATIVE_NATIVEPROCESS_MATRIX_H_