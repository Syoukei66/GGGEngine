#ifndef HAL_ENGINE_NATIVE_NATIVEPROCESS_MATRIX_H_
#define HAL_ENGINE_NATIVE_NATIVEPROCESS_MATRIX_H_

#include "NativeType.h"
#include "Geometry.h"

class INativeProcess_Matrix
{
  // =================================================================
  // Method
  // =================================================================
public:
  virtual LP_MATRIX_4x4 Matrix4x4_GetIdentity() const = 0;

  virtual LP_MATRIX_4x4 Matrix4x4_Create() const = 0;
  virtual void Matrix4x4_Init(LP_MATRIX_4x4 matrix) const = 0;
  virtual void Matrix4x4_Delete(LP_MATRIX_4x4 matrix) const = 0;
  virtual void Matrix4x4_Assign(LP_MATRIX_4x4 dst, LP_MATRIX_4x4 mat) const = 0;

  virtual void Matrix4x4_Inverse(LP_MATRIX_4x4 dst, LP_MATRIX_4x4 mat) const = 0;
  virtual void Matrix4x4_Multiply(LP_MATRIX_4x4 dst, LP_MATRIX_4x4 mat) const = 0;

  virtual void Matrix4x4_Translate(LP_MATRIX_4x4 mat, T_FLOAT x, T_FLOAT y, T_FLOAT z) const = 0;
  virtual void Matrix4x4_Scaling(LP_MATRIX_4x4 mat, T_FLOAT x, T_FLOAT y, T_FLOAT z) const = 0;
  virtual void Matrix4x4_Rotation(LP_MATRIX_4x4 mat, T_FLOAT x, T_FLOAT y, T_FLOAT z) const = 0;

  virtual void Matrix4x4_Apply(LP_MATRIX_4x4 mat, TVec2f* dest) const = 0;
  virtual void Matrix4x4_Apply(LP_MATRIX_4x4 mat, TVec3f* dest) const = 0;
  virtual void Matrix4x4_Apply(LP_MATRIX_4x4 mat, TVec4f* dest) const = 0;
  virtual void Matrix4x4_Apply(LP_MATRIX_4x4 mat, T_FLOAT* dest_x, T_FLOAT* dest_y) const = 0;
  virtual void Matrix4x4_Apply(LP_MATRIX_4x4 mat, T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z) const = 0;
  virtual void Matrix4x4_Apply(LP_MATRIX_4x4 mat, T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z, T_FLOAT* dest_w) const = 0;

  virtual void Matrix4x4_Set(LP_MATRIX_4x4 mat, T_UINT8 x, T_UINT8 y, T_FLOAT value) const = 0;
  virtual T_FLOAT Matrix4x4_Get(LP_MATRIX_4x4 mat, T_UINT8 x, T_UINT8 y) const = 0;

  virtual void Matrix4x4_Direction(LP_MATRIX_4x4 mat, TVec3f* dest) const = 0;

  virtual void Matrix4x4_LookAtLH(LP_MATRIX_4x4 mat, const TVec3f& camera_pos, const TVec3f& camera_at, const TVec3f& camera_up) const = 0;
  virtual void Matrix4x4_PerspectiveFovLH(LP_MATRIX_4x4 mat, T_FLOAT field_of_view_y, T_FLOAT aspect_ratio, T_FLOAT z_near, T_FLOAT z_far) const = 0;
  virtual void Matrix4x4_OrthoLH(LP_MATRIX_4x4 mat, T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far) const = 0;

  virtual LP_MATRIX_4x4_STACK Matrix4x4Stack_Create() const = 0;
  virtual void Matrix4x4Stack_Push(LP_MATRIX_4x4_STACK stack, LP_MATRIX_4x4 matrix) const = 0;
  virtual void Matrix4x4Stack_Pop(LP_MATRIX_4x4_STACK stack) const = 0;
  virtual void Matrix4x4Stack_Delete(LP_MATRIX_4x4_STACK stack) const = 0;
  virtual void Matrix4x4Stack_Apply(LP_DEVICE device, LP_MATRIX_4x4_STACK stack) const = 0;
  virtual LP_MATRIX_4x4 Matrix4x4Stack_GetTop(LP_MATRIX_4x4_STACK stack) const = 0;
};

#endif//HAL_ENGINE_NATIVE_NATIVEPROCESS_MATRIX_H_
