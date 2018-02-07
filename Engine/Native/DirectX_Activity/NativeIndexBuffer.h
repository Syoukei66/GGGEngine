#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <NativeIndexBuffer.h>

class NativeIndexBuffer : public INativeIndexBuffer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeIndexBuffer(T_UINT16 vertex_count);
  ~NativeIndexBuffer();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) override;
  virtual void Unlock() override;
  virtual void SetIndices() const override;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  virtual T_UINT16 GetVertexesCount() const override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  const T_UINT16 vertex_count_;
  IDirect3DIndexBuffer9* index_buffer_;
};