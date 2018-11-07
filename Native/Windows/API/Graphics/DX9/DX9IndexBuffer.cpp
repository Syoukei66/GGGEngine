#include "DX9IndexBuffer.h"

#include "DX9GraphicsAPI.h"

// =================================================================
// Constructor / Destructor
// =================================================================
DX9IndexBuffer::DX9IndexBuffer(T_UINT32 vertex_count, T_UINT32 polygon_count)
  : vertex_count_(vertex_count)
  , polygon_count_(polygon_count)
{
  LPDIRECT3DDEVICE9 device = DX9GraphicsAPI::GetInstance()->GetDevice();
  HRESULT hr = device->CreateIndexBuffer(
    sizeof(T_UINT32) * vertex_count,
    0,
    D3DFMT_INDEX32,
    D3DPOOL_MANAGED,
    &this->index_buffer_,
    NULL
  );
  GG_ASSERT(SUCCEEDED(hr), "IndexBufferの作成に失敗しました");
}

DX9IndexBuffer::~DX9IndexBuffer()
{
  this->index_buffer_->Release();
}

// =================================================================
// Method
// =================================================================
void DX9IndexBuffer::Lock(void** dest)
{
  HRESULT hr = this->index_buffer_->Lock(0, 0, dest, 0);
  GG_ASSERT(SUCCEEDED(hr), "IndexBufferのロックに失敗しました");
}

void DX9IndexBuffer::Unlock()
{
  HRESULT hr = this->index_buffer_->Unlock();
  GG_ASSERT(SUCCEEDED(hr), "IndexBufferのアンロックに失敗しました");
}

void DX9IndexBuffer::SetIndices() const
{
  LPDIRECT3DDEVICE9 device = DX9GraphicsAPI::GetInstance()->GetDevice();

  HRESULT hr = device->SetIndices(this->index_buffer_);
  GG_ASSERT(SUCCEEDED(hr), "IndexBufferのセットに失敗しました");
}
