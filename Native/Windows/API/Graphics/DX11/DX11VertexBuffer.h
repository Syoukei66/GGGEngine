#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Resource/VertexBuffer/VertexBuffer.h>

class DX11VertexBuffer : public rcVertexBuffer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX11VertexBuffer(T_UINT32 size);
  DX11VertexBuffer(T_UINT32 size, void* data);
  ~DX11VertexBuffer();

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

UniqueRef<rcVertexBuffer> rcVertexBuffer::Create(T_UINT32 size)
{
  return UniqueRef<rcVertexBuffer>(new DX11VertexBuffer(size));
}
UniqueRef<rcVertexBuffer> rcVertexBuffer::Create(T_UINT32 size, void* data)
{
  return UniqueRef<rcVertexBuffer>(new DX11VertexBuffer(size, data));
}

#endif
