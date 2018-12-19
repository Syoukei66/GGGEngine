#include "DX11ConstantBuffer.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>

// =================================================================
// Constructor / Destructor
// =================================================================
DX11ConstantBuffer::DX11ConstantBuffer(Shader::ConstantBufferId id, T_UINT32 size)
  : rcConstantBuffer(id)
{
  if (size == 0)
  {
    this->constant_buffer_ = nullptr;
    return;
  }
  ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();

  D3D11_BUFFER_DESC desc = D3D11_BUFFER_DESC();
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.ByteWidth = size;
  desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  desc.CPUAccessFlags = 0;
  desc.MiscFlags = 0;
  desc.StructureByteStride = 0;
  
  HRESULT hr = device->CreateBuffer(
    &desc, NULL, &this->constant_buffer_
  );
  GG_ASSERT(SUCCEEDED(hr), "定数バッファの作成に失敗しました");
}

DX11ConstantBuffer::DX11ConstantBuffer(Shader::ConstantBufferId id, T_UINT32 size, const void* data)
  : rcConstantBuffer(id)
{
  if (size == 0)
  {
    this->constant_buffer_ = nullptr;
    return;
  }
  ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();
  
  D3D11_BUFFER_DESC desc = D3D11_BUFFER_DESC();
  desc.Usage = D3D11_USAGE_IMMUTABLE;
  desc.ByteWidth = size;
  desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  desc.CPUAccessFlags = 0;
  desc.MiscFlags = 0;
  desc.StructureByteStride = 0;

  D3D11_SUBRESOURCE_DATA sub_data;
  sub_data.pSysMem = data;
  sub_data.SysMemPitch = 0;
  sub_data.SysMemSlicePitch = 0;

  HRESULT hr = device->CreateBuffer(
    &desc, &sub_data, &this->constant_buffer_
  );
  GG_ASSERT(SUCCEEDED(hr), "定数バッファの作成に失敗しました");
}

DX11ConstantBuffer::~DX11ConstantBuffer()
{
  if (this->constant_buffer_)
  {
    this->constant_buffer_->Release();
  }
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
void DX11ConstantBuffer::CommitChanges(const void* data)
{
  if (!this->constant_buffer_)
  {
    return;
  }
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  context->UpdateSubresource(this->constant_buffer_, 0, NULL, data, 0, 0);
}

void DX11ConstantBuffer::SetBuffer() const
{
  if (!this->constant_buffer_)
  {
    return;
  }
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  context->VSSetConstantBuffers(static_cast<T_UINT8>(this->id_), 1, &this->constant_buffer_);
  context->PSSetConstantBuffers(static_cast<T_UINT8>(this->id_), 1, &this->constant_buffer_);
}

#endif