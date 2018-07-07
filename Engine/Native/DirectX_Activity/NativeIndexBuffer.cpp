#include "NativeIndexBuffer.h"
#include "Director.h"

// =================================================================
// Constructor / Destructor
// =================================================================
NativeIndexBuffer::NativeIndexBuffer(T_UINT16 vertex_count)
  : vertex_count_(vertex_count)
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  HRESULT hr = device->CreateIndexBuffer(
    sizeof(T_UINT32) * vertex_count,
    0,
    D3DFMT_INDEX32,
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
  HRESULT hr = this->index_buffer_->Lock(0, 0, dest, 0);
  NATIVE_ASSERT(SUCCEEDED(hr), "IndexBuffer�̃��b�N�Ɏ��s���܂���");
}

void NativeIndexBuffer::Unlock()
{
  HRESULT hr = this->index_buffer_->Unlock();
  NATIVE_ASSERT(SUCCEEDED(hr), "IndexBuffer�̃A�����b�N�Ɏ��s���܂���");
}

void NativeIndexBuffer::SetIndices() const
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  HRESULT hr = device->SetIndices(this->index_buffer_);
  NATIVE_ASSERT(SUCCEEDED(hr), "IndexBuffer�̃Z�b�g�Ɏ��s���܂���");
}

// =================================================================
// setter/getter
// =================================================================
T_UINT16 NativeIndexBuffer::GetVertexesCount() const
{
  return this->vertex_count_;
}
