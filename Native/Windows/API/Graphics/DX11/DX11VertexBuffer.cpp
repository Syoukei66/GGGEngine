#include "DX11VertexBuffer.h"

#if GG_GRAPHICS_API_DX11

#include <Core/Application/Platform/API/_Resource/VertexDeclaration/VertexDeclaration.h>
#include <Native/Windows/WindowsApplication.h>

#include "DX11Constants.h"
#include "DX11GraphicsAPI.h"

// =================================================================
// Constructor / Destructor
// =================================================================
DX11VertexBuffer::DX11VertexBuffer(T_UINT32 size)
{
  ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();

  D3D11_BUFFER_DESC buffer_desc;
  buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
  buffer_desc.ByteWidth = size;
  buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  buffer_desc.CPUAccessFlags = 0;
  buffer_desc.MiscFlags = 0;
  buffer_desc.StructureByteStride = 0;

  HRESULT hr = device->CreateBuffer(
    &buffer_desc, NULL, &this->vertex_buffer_
  );
  GG_ASSERT(SUCCEEDED(hr), "VertexBuffer‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

DX11VertexBuffer::DX11VertexBuffer(T_UINT32 size, void* data)
{
  ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();

  D3D11_BUFFER_DESC buffer_desc;
  buffer_desc.Usage = D3D11_USAGE_IMMUTABLE;
  buffer_desc.ByteWidth = size;
  buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  buffer_desc.CPUAccessFlags = 0;
  buffer_desc.MiscFlags = 0;
  buffer_desc.StructureByteStride = 0;

  D3D11_SUBRESOURCE_DATA sub_data;
  sub_data.pSysMem = data;
  sub_data.SysMemPitch = 0;
  sub_data.SysMemSlicePitch = 0;

  HRESULT hr = device->CreateBuffer(
    &buffer_desc, &sub_data, &this->vertex_buffer_
  );
  GG_ASSERT(SUCCEEDED(hr), "VertexBuffer‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

DX11VertexBuffer::~DX11VertexBuffer()
{
  this->vertex_buffer_->Release();
}

// =================================================================
// Method
// =================================================================
void DX11VertexBuffer::Lock(void** dest)
{
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  D3D11_MAPPED_SUBRESOURCE mapped_subresource;
  HRESULT hr = context->Map(this->vertex_buffer_, 0, D3D11_MAP_WRITE, 0, &mapped_subresource);
  GG_ASSERT(SUCCEEDED(hr), "VertexBuffer‚ÌƒƒbƒN‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
  (*dest) = mapped_subresource.pData;
}

void DX11VertexBuffer::Unlock()
{
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  context->Unmap(this->vertex_buffer_, 0);
}

void DX11VertexBuffer::SetStreamSource(const SharedRef<const rcVertexDeclaration>& declaration) const
{
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  T_UINT32 stride = declaration->GetVertexSize();
  context->IASetVertexBuffers(
    0,
    1,
    &this->vertex_buffer_,
    &stride,
    0
  );
}

#endif
