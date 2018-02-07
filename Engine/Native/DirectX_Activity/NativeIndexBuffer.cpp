#include "NativeIndexBuffer.h"
#include "Director.h"

// =================================================================
// Constructor / Destructor
// =================================================================
NativeIndexBuffer::NativeIndexBuffer(T_UINT16 vertex_count)
  : vertex_count_(vertex_count)
{
  static const D3DFORMAT format = sizeof(T_UINT16) == 2 ? D3DFMT_INDEX16 : D3DFMT_INDEX32;
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  HRESULT hr = device->CreateIndexBuffer(
    sizeof(T_UINT16) * vertex_count,
    0,
    format,
    D3DPOOL_MANAGED,
    &this->index_buffer_,
    NULL
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "IndexBuffer�̍쐬�Ɏ��s���܂���");
}

NativeIndexBuffer::~NativeIndexBuffer()
{
  this->index_buffer_->Release();
}

// =================================================================
// Method
// =================================================================
void NativeIndexBuffer::Lock(void** dest)
{
  this->index_buffer_->Lock(0, 0, dest, 0);
}

void NativeIndexBuffer::Unlock()
{
  this->index_buffer_->Unlock();
}

void NativeIndexBuffer::SetIndices() const
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->SetIndices(this->index_buffer_);
}

// =================================================================
// setter/getter
// =================================================================
T_UINT16 NativeIndexBuffer::GetVertexesCount() const
{
  return this->vertex_count_;
}
