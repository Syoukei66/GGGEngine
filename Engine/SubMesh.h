#pragma once

#include "MeshData.h"
#include "NativeVertexBuffer.h"
#include "NativeIndexBuffer.h"

class SubMesh
{
public:
  SubMesh(const MeshData& data);
  ~SubMesh();

  // =================================================================
  // Method
  // =================================================================
public:
  void Draw() const;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline const INativeVertexBuffer* GetVertexBuffer() const
  {
    return this->vertex_buffer_;
  }

  inline const INativeIndexBuffer* GetIndexBuffer() const
  {
    return this->index_buffer_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const MeshData& data_;
  INativeVertexBuffer* vertex_buffer_;
  INativeIndexBuffer* index_buffer_;

};