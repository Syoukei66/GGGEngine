#include "DX11IndexBuffer.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>

#include "DX11Constants.h"

UniqueRef<rcIndexBuffer> rcIndexBuffer::Create(T_UINT32 vertex_count, T_UINT32 polygon_count, Vertex::IndexFormat format)
{
  return UniqueRef<rcIndexBuffer>(new DX11IndexBuffer(vertex_count, polygon_count, format));
}

UniqueRef<rcIndexBuffer> rcIndexBuffer::Create(T_UINT32 vertex_count, T_UINT32 polygon_count, Vertex::IndexFormat format, void* data)
{
  return UniqueRef<rcIndexBuffer>(new DX11IndexBuffer(vertex_count, polygon_count, format, data));
}

// =================================================================
// Constructor / Destructor
// =================================================================
DX11IndexBuffer::DX11IndexBuffer(T_UINT32 vertex_count, T_UINT32 polygon_count, Vertex::IndexFormat format)
  : vertex_count_(vertex_count)
  , polygon_count_(polygon_count)
  , format_(format)
{
  const T_UINT8 format_index = static_cast<T_UINT8>(this->format_);

  ID3D11Device* device = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetDevice();

  D3D11_BUFFER_DESC buffer_desc;
  buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
  buffer_desc.ByteWidth = vertex_count * Vertex::INDEX_FORMAT_SIZES[format_index];
  buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  buffer_desc.MiscFlags = 0;
  buffer_desc.StructureByteStride = 0;

  HRESULT hr = device->CreateBuffer(
    &buffer_desc, NULL, &this->index_buffer_
  );
  GG_ASSERT(SUCCEEDED(hr), "IndexBufferÇÃçÏê¨Ç…é∏îsÇµÇ‹ÇµÇΩ");
}

DX11IndexBuffer::DX11IndexBuffer(T_UINT32 vertex_count, T_UINT32 polygon_count, Vertex::IndexFormat format, void * data)
  : vertex_count_(vertex_count)
  , polygon_count_(polygon_count)
  , format_(format)
{
  const T_UINT8 format_index = static_cast<T_UINT8>(this->format_);

  ID3D11Device* device = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetDevice();

  D3D11_BUFFER_DESC buffer_desc;
  buffer_desc.Usage = D3D11_USAGE_IMMUTABLE;
  buffer_desc.ByteWidth = vertex_count * Vertex::INDEX_FORMAT_SIZES[format_index];
  buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  buffer_desc.CPUAccessFlags = 0;
  buffer_desc.MiscFlags = 0;
  buffer_desc.StructureByteStride = 0;

  D3D11_SUBRESOURCE_DATA sub_data;
  sub_data.pSysMem = data;
  sub_data.SysMemPitch = 0;
  sub_data.SysMemSlicePitch = 0;

  HRESULT hr = device->CreateBuffer(
    &buffer_desc, &sub_data, &this->index_buffer_
  );
  GG_ASSERT(SUCCEEDED(hr), "IndexBufferÇÃçÏê¨Ç…é∏îsÇµÇ‹ÇµÇΩ");
}

DX11IndexBuffer::~DX11IndexBuffer()
{
  this->index_buffer_->Release();
}

// =================================================================
// Method
// =================================================================
void DX11IndexBuffer::Lock(void** dest)
{
  ID3D11DeviceContext* context = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetImmediateContext();
  D3D11_MAPPED_SUBRESOURCE mapped_subresource;
  HRESULT hr = context->Map(this->index_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource);
  GG_ASSERT(SUCCEEDED(hr), "VertexBufferÇÃÉçÉbÉNÇ…é∏îsÇµÇ‹ÇµÇΩ");
  (*dest) = mapped_subresource.pData;
}

void DX11IndexBuffer::Unlock()
{
  ID3D11DeviceContext* context = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetImmediateContext();
  context->Unmap(this->index_buffer_, 0);
}

void DX11IndexBuffer::SetIndices() const
{
  const T_UINT8 format_index = static_cast<T_UINT8>(this->format_);
  ID3D11DeviceContext* context = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetImmediateContext();
  context->IASetIndexBuffer(
    this->index_buffer_,
    DX11::INDEX_FORMATS[format_index],
    0
  );
}

T_UINT32 DX11IndexBuffer::GetVertexCount() const
{
  return this->vertex_count_;
}

T_UINT32 DX11IndexBuffer::GetPolygonCount() const
{
  return this->polygon_count_;
}

Vertex::IndexFormat DX11IndexBuffer::GetIndexFormat() const
{
  return this->format_;
}

#endif