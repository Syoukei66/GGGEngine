#include "NativeMatrixStack.h"

#include <d3d9.h>
#include <d3dx9.h>

#define stack_ GetNativeInstance<ID3DXMatrixStack>()

// =================================================================
// Constructor / Destructor
// =================================================================
NativeMatrixStack::NativeMatrixStack()
{
  LPD3DXMATRIXSTACK stack;
  D3DXCreateMatrixStack(0, &stack);
  this->SetNativeInstance<ID3DXMatrixStack>(stack);
}

NativeMatrixStack::~NativeMatrixStack()
{
  this->stack_->Release();
}

// =================================================================
// Method
// =================================================================
void NativeMatrixStack::Push(const Matrix4x4& mat)
{
  this->stack_->Push();
  this->stack_->MultMatrixLocal((const D3DXMATRIX*)&mat);
}

void NativeMatrixStack::Pop()
{
  this->stack_->Pop();
}

const Matrix4x4& NativeMatrixStack::GetTop()
{
  return (const Matrix4x4&)*this->stack_->GetTop();
}
