#include "NativeProcess_Matrix.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "../../Engine/Director.h"

static LP_MATRIX_4x4 IDENTITY_MATRIX = nullptr;

//平行移動      _41 _42 _43
//スケーリング  _11 _22 _33

LP_MATRIX_4x4 NativeProcess_Matrix::Matrix4x4_GetIdentity() const
{
  if (!IDENTITY_MATRIX)
  {
    IDENTITY_MATRIX = this->Matrix4x4_Create();
  }
  return IDENTITY_MATRIX;
}

LP_MATRIX_4x4 NativeProcess_Matrix::Matrix4x4_Create() const
{
  LP_MATRIX_4x4 ret = (LP_MATRIX_4x4)new D3DXMATRIX();
  this->Matrix4x4_Init(ret);
  return ret;
}

void NativeProcess_Matrix::Matrix4x4_Init(LP_MATRIX_4x4 matrix) const
{
  D3DXMatrixIdentity((D3DXMATRIX*)matrix);
}

void NativeProcess_Matrix::Matrix4x4_Delete(LP_MATRIX_4x4 matrix) const
{
  if (matrix)
  {
    delete (D3DXMATRIX*)matrix;
  }
}

void NativeProcess_Matrix::Matrix4x4_Assign(LP_MATRIX_4x4 dst, LP_MATRIX_4x4 mat) const
{
  D3DXMatrixIdentity((D3DXMATRIX*)dst);
  D3DXMatrixMultiply((D3DXMATRIX*)dst, (D3DXMATRIX*)dst, (D3DXMATRIX*)mat);
}

void NativeProcess_Matrix::Matrix4x4_Inverse(LP_MATRIX_4x4 dst, LP_MATRIX_4x4 mat) const
{
  D3DXMatrixInverse((D3DXMATRIX*)dst, NULL, (D3DXMATRIX*) mat);
}

void NativeProcess_Matrix::Matrix4x4_Multiply(LP_MATRIX_4x4 dst, LP_MATRIX_4x4 mat) const
{
  D3DXMatrixMultiply((D3DXMATRIX*)dst, (D3DXMATRIX*)dst, (D3DXMATRIX*)mat);
}

void NativeProcess_Matrix::Matrix4x4_Translate(LP_MATRIX_4x4 mat, T_FLOAT x, T_FLOAT y, T_FLOAT z) const
{
  D3DXMatrixTranslation((D3DXMATRIX*)mat, x, y, z);
}

void NativeProcess_Matrix::Matrix4x4_Scaling(LP_MATRIX_4x4 mat, T_FLOAT x, T_FLOAT y, T_FLOAT z) const
{
  D3DXMatrixScaling((D3DXMATRIX*)mat, x, y, z);
}

void NativeProcess_Matrix::Matrix4x4_Rotation(LP_MATRIX_4x4 mat, T_FLOAT x, T_FLOAT y, T_FLOAT z) const
{
  D3DXMATRIX matX, matY, matZ;
  D3DXMatrixRotationX(&matX, x);
  D3DXMatrixRotationY(&matY, y);
  D3DXMatrixRotationZ(&matZ, z);
  D3DXMatrixIdentity((D3DXMATRIX*)mat);
  D3DXMatrixMultiply((D3DXMATRIX*)mat, &matX, (D3DXMATRIX*)mat);
  D3DXMatrixMultiply((D3DXMATRIX*)mat, &matY, (D3DXMATRIX*)mat);
  D3DXMatrixMultiply((D3DXMATRIX*)mat, &matZ, (D3DXMATRIX*)mat);
}

void NativeProcess_Matrix::Matrix4x4_Apply(LP_MATRIX_4x4 mat, TVec2f* dest) const
{
  this->Matrix4x4_Apply(mat, &dest->x, &dest->y, nullptr, nullptr);
}

void NativeProcess_Matrix::Matrix4x4_Apply(LP_MATRIX_4x4 mat, TVec3f* dest) const
{
  this->Matrix4x4_Apply(mat, &dest->x, &dest->y, &dest->z, nullptr);
}

void NativeProcess_Matrix::Matrix4x4_Apply(LP_MATRIX_4x4 mat, TVec4f* dest) const
{
  this->Matrix4x4_Apply(mat, &dest->x, &dest->y, &dest->z, &dest->w);
}

void NativeProcess_Matrix::Matrix4x4_Apply(LP_MATRIX_4x4 mat, T_FLOAT* dest_x, T_FLOAT* dest_y) const
{
  this->Matrix4x4_Apply(mat, dest_x, dest_y, nullptr, nullptr);
}

void NativeProcess_Matrix::Matrix4x4_Apply(LP_MATRIX_4x4 mat, T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z) const
{
  this->Matrix4x4_Apply(mat, dest_x, dest_y, dest_z, nullptr);
}

void NativeProcess_Matrix::Matrix4x4_Apply(LP_MATRIX_4x4 mat, T_FLOAT* dest_x, T_FLOAT* dest_y, T_FLOAT* dest_z, T_FLOAT* dest_w) const
{
  D3DXMATRIX* matrix = (D3DXMATRIX*)mat;
  const T_FLOAT x = dest_x ? (*dest_x) : 0.0f;
  const T_FLOAT y = dest_y ? (*dest_y) : 0.0f;
  const T_FLOAT z = dest_z ? (*dest_z) : 0.0f;
  const T_FLOAT w = dest_w ? (*dest_w) : 1.0f;
  if (dest_x)
  {
    (*dest_x) = (x * matrix->_11) + (y * matrix->_21) + (z * matrix->_31) + (w * matrix->_41);
  }
  if (dest_y)
  {
    (*dest_y) = (x * matrix->_12) + (y * matrix->_22) + (z * matrix->_32) + (w * matrix->_42);
  }
  if (dest_z)
  {
    (*dest_z) = (x * matrix->_13) + (y * matrix->_23) + (z * matrix->_33) + (w * matrix->_43);
  }
  if (dest_w)
  {
    (*dest_w) = (x * matrix->_14) + (y * matrix->_24) + (z * matrix->_34) + (w * matrix->_44);
  }
}

void NativeProcess_Matrix::Matrix4x4_Set(LP_MATRIX_4x4 mat, T_UINT8 x, T_UINT8 y, T_FLOAT value) const
{
  D3DXMATRIX* matrix = (D3DXMATRIX*)mat;
  matrix->m[x][y] = value;
}

T_FLOAT NativeProcess_Matrix::Matrix4x4_Get(LP_MATRIX_4x4 mat, T_UINT8 x, T_UINT8 y) const
{
  D3DXMATRIX* matrix = (D3DXMATRIX*)mat;
  return matrix->m[x][y];
}

void NativeProcess_Matrix::Matrix4x4_Direction(LP_MATRIX_4x4 mat, TVec3f * dest) const
{
  D3DXMATRIX* matrix = (D3DXMATRIX*)mat;
  dest->x = -matrix->_31;
  dest->y = -matrix->_32;
  dest->z = matrix->_33;
}

void NativeProcess_Matrix::Matrix4x4_LookAtLH(LP_MATRIX_4x4 mat, const TVec3f& camera_pos, const TVec3f& camera_at, const TVec3f& camera_up) const
{
  D3DXMatrixLookAtLH(
    (LPD3DXMATRIX)mat,
    &D3DXVECTOR3(camera_pos.x, camera_pos.y, camera_pos.z),
    &D3DXVECTOR3(camera_at.x, camera_at.y, camera_at.z),
    &D3DXVECTOR3(camera_up.x, camera_up.y, camera_up.z)
    );
}

void NativeProcess_Matrix::Matrix4x4_PerspectiveFovLH(LP_MATRIX_4x4 mat, T_FLOAT field_of_view_y, T_FLOAT aspect_ratio, T_FLOAT z_near, T_FLOAT z_far) const
{
  D3DXMatrixPerspectiveFovLH(
    (LPD3DXMATRIX)mat,
    field_of_view_y,
    aspect_ratio,
    z_near,
    z_far
  );
}

void NativeProcess_Matrix::Matrix4x4_OrthoLH(LP_MATRIX_4x4 mat, T_FLOAT width, T_FLOAT height, T_FLOAT z_near, T_FLOAT z_far) const
{
  D3DXMatrixOrthoLH(
    (LPD3DXMATRIX)mat,
    width,
    height,
    z_near,
    z_far
  );
}

LP_MATRIX_4x4_STACK NativeProcess_Matrix::Matrix4x4Stack_Create() const
{
  LPD3DXMATRIXSTACK* stack = new LPD3DXMATRIXSTACK();
  D3DXCreateMatrixStack(0, stack);
  return (LP_MATRIX_4x4_STACK)(*stack);
}

void NativeProcess_Matrix::Matrix4x4Stack_Push(LP_MATRIX_4x4_STACK stack, LP_MATRIX_4x4 matrix) const
{
  LPD3DXMATRIXSTACK casted_stack = (LPD3DXMATRIXSTACK)stack;
  casted_stack->Push();
  casted_stack->MultMatrixLocal((D3DXMATRIX*)matrix);
}

void NativeProcess_Matrix::Matrix4x4Stack_Pop(LP_MATRIX_4x4_STACK stack) const
{
  LPD3DXMATRIXSTACK casted_stack = (LPD3DXMATRIXSTACK)stack;
  casted_stack->Pop();
}

void NativeProcess_Matrix::Matrix4x4Stack_Delete(LP_MATRIX_4x4_STACK stack) const
{
  LPD3DXMATRIXSTACK casted_stack = (LPD3DXMATRIXSTACK)stack;
  casted_stack->Release();
}

void NativeProcess_Matrix::Matrix4x4Stack_Apply(LP_DEVICE device, LP_MATRIX_4x4_STACK stack) const
{
  LPDIRECT3DDEVICE9 casted_device = (LPDIRECT3DDEVICE9)device;
  D3DXMATRIX* mat = ((LPD3DXMATRIXSTACK)stack)->GetTop();
  casted_device->SetTransform(D3DTS_WORLD, mat);
}

LP_MATRIX_4x4 NativeProcess_Matrix::Matrix4x4Stack_GetTop(LP_MATRIX_4x4_STACK stack) const
{
  return (LP_MATRIX_4x4)((LPD3DXMATRIXSTACK)stack)->GetTop();
}
