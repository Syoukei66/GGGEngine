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
  NativeVertexBuffer(T_UINT16 vertex_count, INativeProcess_Graphics::VertexType vertex_type);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) override;
  virtual void Unlock() override;
  virtual void Draw(INativeProcess_Graphics::PrimitiveType primitive_type) override;
  virtual void DrawIndexed(const INativeIndexBuffer* index_buffer, INativeProcess_Graphics::PrimitiveType primitive_type) override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  const T_UINT16 vertex_count_;
  const INativeProcess_Graphics::VertexType vertex_type_;
  IDirect3DVertexBuffer9* vertex_buffer_;

};