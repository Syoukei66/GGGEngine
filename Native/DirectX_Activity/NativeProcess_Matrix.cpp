#include "NativeProcess_Matrix.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "../../Engine/Director.h"

//static LP_MATRIX_4x4 IDENTITY_MATRIX = nullptr;
//
////平行移動      _41 _42 _43
////スケーリング  _11 _22 _33
//
//LP_MATRIX_4x4 NativeProcess_Matrix::Matrix4x4_GetIdentity() const
//{
//  if (!IDENTITY_MATRIX)
//  {
//    IDENTITY_MATRIX = this->Matrix4x4_Create();
//  }
//  return IDENTITY_MATRIX;
//}

T_FLOAT NativeProcess_Matrix::Matrix4x4_Get(LP_MATRIX_4x4 mat, T_UINT8 x, T_UINT8 y) const
{
  D3DXMATRIX* matrix = (D3DXMATRIX*)mat;
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
