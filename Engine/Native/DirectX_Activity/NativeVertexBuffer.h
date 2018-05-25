#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <NativeVertexBuffer.h>

class NativeVertexBuffer : public INativeVertexBuffer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeVertexBuffer(T_UINT16 vertex_count, T_UINT16 polygon_count, T_UINT32 format);
  ~NativeVertexBuffer();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) override;
  virtual void Unlock() override;

  virtual void SetStreamSource() const override;
  virtual void DrawPrimitive(INativeProcess_Graphics::PrimitiveType primitive_type) const override;
  virtual void DrawIndexedPrimitive(const INativeIndexBuffer* index_buffer, INativeProcess_Graphics::PrimitiveType primitive_type) const override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  const T_UINT16 vertex_count_;
  const T_UINT16 polygon_count_;
  const T_UINT32 format_;
  T_UINT32 stride_;
  IDirect3DVertexBuffer9* vertex_buffer_;
  IDirect3DVertexDeclaration9* vertex_declaration_;
};