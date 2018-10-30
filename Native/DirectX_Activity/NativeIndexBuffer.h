#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class NativeIndexBuffer : public rcIndexBuffer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeIndexBuffer(T_UINT32 vertex_count, T_UINT32 polygon_count);
  ~NativeIndexBuffer();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) override;
  virtual void Unlock() override;
  virtual void SetIndices() const override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual GG_INLINE T_UINT32 GetVertexesCount() const override
  {
    return this->vertex_count_;
  }
  virtual GG_INLINE T_UINT32 GetPolygonCount() const override
  {
    return this->polygon_count_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const T_UINT32 vertex_count_;
  const T_UINT32 polygon_count_;
  IDirect3DIndexBuffer9* index_buffer_;
};