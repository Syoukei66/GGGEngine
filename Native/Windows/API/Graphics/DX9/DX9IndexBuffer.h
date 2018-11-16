#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <Core/Application/Platform/API/_Resource/IndexBuffer/IndexBuffer.h>

class DX9IndexBuffer : public rcIndexBuffer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX9IndexBuffer(T_UINT32 vertex_count, T_UINT32 polygon_count, Vertex::IndexFormat format);
  ~DX9IndexBuffer();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) override;
  virtual void Unlock() override;
  virtual void SetIndices() const override;
  virtual T_UINT32 GetVertexCount() const override;
  virtual T_UINT32 GetPolygonCount() const override;
  virtual Vertex::IndexFormat GetIndexFormat() const override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT32 vertex_count_;
  T_UINT32 polygon_count_;
  Vertex::IndexFormat format_;
  IDirect3DIndexBuffer9* index_buffer_;
};