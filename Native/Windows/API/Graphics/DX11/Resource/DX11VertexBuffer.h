#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Resource/VertexBuffer.h>

class DX11VertexBuffer : public rcVertexBuffer
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(DX11VertexBuffer);
  GG_CREATE_FUNC_1(DX11VertexBuffer, T_UINT32, size);
  GG_CREATE_FUNC_2(DX11VertexBuffer, T_UINT32, size, void*, data);
  GG_DESTRUCT_FUNC(DX11VertexBuffer);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) override;
  virtual void Unlock() override;
  virtual void SetStreamSource(const SharedRef<const rcVertexDeclaration>& declaration) const override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  ID3D11Buffer* vertex_buffer_;
};

#endif
