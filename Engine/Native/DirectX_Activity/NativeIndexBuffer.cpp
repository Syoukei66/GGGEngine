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
    sizeof(T_UINT16) * vertex_count,
    0,
    D3DFMT_INDEX16,
    D3DPOOL_MANAGED,
    &this->index_buffer_,
    NULL
  );
  NATIVE_ASSERT(hr, "IndexBuffer‚Ìì¬‚É¸”s‚µ‚Ü‚µ‚½");
}

// =================================================================
// Method
// =================================================================
void NativeIndexBuffer::SetIndices() const
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->SetIndices(this->index_buffer_);
}

T_UINT16 NativeIndexBuffer::GetVertexesCount() const
{
  return this->vertex_count_;
}
