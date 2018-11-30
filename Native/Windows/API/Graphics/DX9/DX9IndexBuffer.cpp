#include "DX9IndexBuffer.h"

#if GG_GRAPHICS_API_DX9

#include <Native/Windows/WindowsApplication.h>

#include "DX9GraphicsAPI.h"
#include "DX9Constants.h"

// =================================================================
// Constructor / Destructor
// =================================================================
DX9IndexBuffer::DX9IndexBuffer(T_UINT32 vertex_count, T_UINT32 polygon_count, Vertex::IndexFormat format)
  : vertex_count_(vertex_count)
  , polygon_count_(polygon_count)
  , format_(format)
{
  const T_UINT8 format_index = static_cast<T_UINT8>(this->format_);

  LPDIRECT3DDEVICE9 device = WindowsApplication::GetDX9Graphics()->GetDevice();
  HRESULT hr = device->CreateIndexBuffer(
    vertex_count * Vertex::INDEX_FORMAT_SIZES[format_index],
    0,
    DX9::INDEX_FORMATS[format_index],
    D3DPOOL_MANAGED,
    &this->index_buffer_,
    NULL
  );
  GG_ASSERT(SUCCEEDED(hr), "IndexBuffer‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
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
  GG_ASSERT(SUCCEEDED(hr), "IndexBuffer‚ÌƒƒbƒN‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

void DX9IndexBuffer::Unlock()
{
  HRESULT hr = this->index_buffer_->Unlock();
  GG_ASSERT(SUCCEEDED(hr), "IndexBuffer‚ÌƒAƒ“ƒƒbƒN‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

void DX9IndexBuffer::SetIndices() const
{
  LPDIRECT3DDEVICE9 device = WindowsApplication::GetDX9Graphics()->GetDevice();

  HRESULT hr = device->SetIndices(this->index_buffer_);
  GG_ASSERT(SUCCEEDED(hr), "IndexBuffer‚ÌƒZƒbƒg‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

T_UINT32 DX9IndexBuffer::GetVertexCount() const
{
  return this->vertex_count_;
}

T_UINT32 DX9IndexBuffer::GetPolygonCount() const
{
  return this->polygon_count_;
}

Vertex::IndexFormat DX9IndexBuffer::GetIndexFormat() const
{
  return this->format_;
}

#endif