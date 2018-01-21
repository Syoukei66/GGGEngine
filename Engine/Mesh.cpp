#include "Mesh.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Mesh::Mesh(const MeshMaterial& material)
  : material_(material)
{
  const T_UINT16 vertexes_count = material.GetVertexesCount();
  this->vertex_buffer_ = INativeVertexBuffer::Create(vertexes_count, material.GetVertexType());
  void* dest_vertexes;
  this->vertex_buffer_->Lock(&dest_vertexes);
  material.SetupVertex(dest_vertexes);
  this->vertex_buffer_->Unlock();

  const T_UINT16 indices_count = material.GetIndicesCount();
  this->index_buffer_ = INativeIndexBuffer::Create(indices_count);
  T_UINT16* dest_indices;
  this->index_buffer_->Lock((void**)&dest_indices);
  const T_UINT16* indices = material.GetIndices();
  for (T_UINT16 i = 0; i < indices_count; ++i)
  {
    dest_indices[i] = indices[i];
  }
  this->index_buffer_->Unlock();
}

Mesh::~Mesh()
{
  delete this->vertex_buffer_;
  delete this->index_buffer_;
  for (Mesh* clone : this->clones_)
  {
    delete clone;
  }
}

// =================================================================
// Method
// =================================================================
Mesh* Mesh::Clone() const
{
  Mesh* mesh = new Mesh(this->material_);
  const_cast<Mesh*>(this)->clones_.push_back(mesh);
  return mesh;
}