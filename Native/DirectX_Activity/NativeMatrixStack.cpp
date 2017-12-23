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
void NativeMatrixStack::Push(NativeMatrixInstance* mat)
{
  this->stack_->Push();
  this->stack_->MultMatrixLocal((D3DXMATRIX*)mat);
}

void NativeMatrixStack::Pop()
{
  this->stack_->Pop();
}

NativeMatrixInstance* NativeMatrixStack::GetTop()
{
  return (NativeMatrixInstance*)this->stack_->GetTop();
}
