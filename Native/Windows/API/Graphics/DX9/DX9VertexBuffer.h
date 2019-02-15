#pragma once

#if GG_GRAPHICS_API_DX9

#include <d3d9.h>
#include <d3dx9.h>

#include <Core/Application/Platform/API/_Resource/VertexBuffer/VertexBuffer.h>

class DX9VertexBuffer : public rcVertexBuffer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX9VertexBuffer(T_UINT32 size);
  DX9VertexBuffer(T_UINT32 size, void* data);
  ~DX9VertexBuffer();

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
  IDirect3DVertexBuffer9* vertex_buffer_;
};

#endif