#pragma once

#include <vector>

#include "NativeVertexBuffer.h"
#include "NativeIndexBuffer.h"
#include "MeshMaterial.h"

class Mesh
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Mesh(const MeshMaterial& material);
  ~Mesh();

  // =================================================================
  // Method
  // =================================================================
public:
  Mesh* Clone() const; 

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
  const MeshMaterial& material_;
  INativeVertexBuffer* vertex_buffer_;
  INativeIndexBuffer* index_buffer_;

  std::vector<Mesh*> clones_;
};