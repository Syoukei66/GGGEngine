#ifndef HAL_ENGINE_NATIVE_NATIVEPROCESS_MATRIX_H_
#define HAL_ENGINE_NATIVE_NATIVEPROCESS_MATRIX_H_

#include "NativeType.h"
#include "Geometry.h"

#include "NativeMatrix.h"

class INativeProcess_Matrix
{
  // =================================================================
  // Method
  // =================================================================
public:
  virtual NativeMatrixInstance* Matrix4x4_GetIdentity() const = 0;

  virtual NativeMatrixInstance* Matrix4x4_Create() const = 0;
  virtual void Matrix4x4_Init(NativeMatrixInstance* matrix) const = 0;
  virtual void Matrix4x4_Delete(NativeMatrixInstance* matrix) const = 0;
  virtual void Matrix4x4_Assign(NativeMatrixInstance* dst, const NativeMatrixInstance& mat) const = 0;

  virtual void Matrix4x4_Inverse(NativeMatrixInstance* dst, NativeMatrixInstance* mat) const = 0;
  virtual void Matrix4x4_Multiply(NativeMatrixInstance* dst, NativeMatrixInstance* mat) const = 0;

  virtual void Matrix4x4_Translate(NativeMatrixInstance* mat, T_FLOAT x, T_FLOAT y, T_FLOAT z) const = 0;
  virtual void Matrix4x4_Scaling(NativeMatrixInstance* mat, T_FLOAT x, T_FLOAT y, T_FLOAT z) const = 0;

  virtual void Matrix4x4_RotationX(NativeMatrixInstance* mat, T_FLOAT x) const = 0;
  virtual void Matrix4x4_RotationY(NativeMatrixInstance* mat, T_FLOAT y) const = 0;
  virtual void Matrix4x4_RotationZ(NativeMatrixInstance* mat, T_FLOAT z) const = 0;

  virtual void Matrix4x4_Apply(NativeMatrixInstance* mat, T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z, T_FLOAT* dest_w) const = 0;

  virtual T_FLOAT* Matrix4x4_Get(NativeMatrixInstance* mat, T_UINT8 x) const = 0;

  virtual void Matrix4x4_Direction(NativeMatrixInstance* mat, TVec3f* dest) const = 0;

  virtual void Matrix4x4_LookAtLH(NativeMatrixInstance* mat, const TVec3f& camera_pos, const TVec3f& camera_at, const TVec3f& camera_up) const = 0;
  virtual void Matrix4x4_PerspectiveFovLH(NativeMatrixInstance* mat, T_FLOAT field_of_view_y, T_FLOAT aspect_ratio, T_FLOAT z_near, T_FLOAT z_far) const = 0;
  virtual void Matrix4x4_OrthoLH(NativeMatrixInstance* mat, T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far) const = 0;

  virtual LP_MATRIX_4x4_STACK Matrix4x4Stack_Create() const = 0;
  virtual void Matrix4x4Stack_Push(LP_MATRIX_4x4_STACK stack, NativeMatrixInstance* matrix) const = 0;
  virtual void Matrix4x4Stack_Pop(LP_MATRIX_4x4_STACK stack) const = 0;
  virtual void Matrix4x4Stack_Delete(LP_MATRIX_4x4_STACK stack) const = 0;
  virtual void Matrix4x4Stack_Apply(LP_DEVICE device, LP_MATRIX_4x4_STACK stack) const = 0;
  virtual NativeMatrixInstance* Matrix4x4Stack_GetTop(LP_MATRIX_4x4_STACK stack) const = 0;
};

#endif//HAL_ENGINE_NATIVE_NATIVEPROCESS_MATRIX_H_
