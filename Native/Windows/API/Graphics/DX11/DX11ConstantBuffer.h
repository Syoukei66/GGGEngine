#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Resource/ConstantBuffer/ConstantBuffer.h>

class DX11ConstantBuffer : public rcConstantBuffer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX11ConstantBuffer(Shader::ConstantBufferId id, T_UINT32 size);
  DX11ConstantBuffer(Shader::ConstantBufferId id, T_UINT32 size, const void* data);
  ~DX11ConstantBuffer();

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void CommitChanges(const void* data) override;
  virtual void SetBuffer() const override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  ID3D11Buffer* constant_buffer_;

};

UniqueRef<rcConstantBuffer> rcConstantBuffer::Create(Shader::ConstantBufferId id, T_UINT32 size)
{
  return UniqueRef<rcConstantBuffer>(new DX11ConstantBuffer(id, size));
}

UniqueRef<rcConstantBuffer> rcConstantBuffer::Create(Shader::ConstantBufferId id, T_UINT32 size, const void* data)
{
  return UniqueRef<rcConstantBuffer>(new DX11ConstantBuffer(id, size, data));
}

#endif

