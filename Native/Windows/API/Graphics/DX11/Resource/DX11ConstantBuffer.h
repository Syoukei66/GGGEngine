#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Resource/ConstantBuffer.h>

class DX11ConstantBuffer : public rcConstantBuffer
{
  // =================================================================
  // GGG Statement
  // =================================================================
public:
  GG_CREATE_FUNC_2(DX11ConstantBuffer, Shader::ConstantBufferId, id, T_UINT32, size);
  GG_CREATE_FUNC_3(DX11ConstantBuffer, Shader::ConstantBufferId, id, T_UINT32, size, const void*, data);
  GG_DESTRUCT_FUNC(DX11ConstantBuffer);

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

#endif

