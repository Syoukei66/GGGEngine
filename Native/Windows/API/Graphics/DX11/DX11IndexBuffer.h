#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>

#include <Core/Application/Platform/API/_Resource/IndexBuffer/IndexBuffer.h>

class DX11IndexBuffer : public rcIndexBuffer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX11IndexBuffer(T_UINT32 vertex_count, T_UINT32 polygon_count, Vertex::IndexFormat format);
  DX11IndexBuffer(T_UINT32 vertex_count, T_UINT32 polygon_count, Vertex::IndexFormat format, void* data);
  ~DX11IndexBuffer();

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
  ID3D11Buffer* index_buffer_;
};

#endif