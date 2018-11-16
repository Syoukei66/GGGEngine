#include "DX9VertexBuffer.h"

#include <Core/Application/Platform/API/_Resource/VertexDeclaration/VertexDeclaration.h>
#include <Native/Windows/WindowsApplication.h>

#include "DX9Constants.h"
#include "DX9GraphicsAPI.h"

// =================================================================
// Constructor / Destructor
// =================================================================
DX9VertexBuffer::DX9VertexBuffer(T_UINT32 size)
{
  LPDIRECT3DDEVICE9 device = WindowsApplication::GetGraphics()->GetDevice();
  HRESULT hr = device->CreateVertexBuffer(
    size,
    0,
    0,
    D3DPOOL_MANAGED,
    &this->vertex_buffer_,
    NULL
  );
  GG_ASSERT(SUCCEEDED(hr), "VertexBufferの作成に失敗しました");
}

DX9VertexBuffer::~DX9VertexBuffer()
{
  this->vertex_buffer_->Release();
}

// =================================================================
// Method
// =================================================================
void DX9VertexBuffer::Lock(void** dest)
{
  HRESULT hr = this->vertex_buffer_->Lock(0, 0, dest, 0);
  GG_ASSERT(SUCCEEDED(hr), "VertexBufferのロックに失敗しました");
}

void DX9VertexBuffer::Unlock()
{
  HRESULT hr = this->vertex_buffer_->Unlock();
  GG_ASSERT(SUCCEEDED(hr), "VertexBufferのアンロックに失敗しました");
}

void DX9VertexBuffer::SetStreamSource(const SharedRef<const rcVertexDeclaration>& declaration) const
{
  declaration->SetVertexDeclaration();
  LPDIRECT3DDEVICE9 device = WindowsApplication::GetGraphics()->GetDevice();
  HRESULT hr = device->SetStreamSource(0, this->vertex_buffer_, 0, declaration->GetVertexSize());
  GG_ASSERT(SUCCEEDED(hr), "VertexBufferのセットに失敗しました");
}

