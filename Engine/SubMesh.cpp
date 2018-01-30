#include "SubMesh.h"

SubMesh::SubMesh(const MeshData& data)
  : data_(data)
{
  const T_UINT16 vertexes_count = data.GetVertexesCount();
  const T_UINT16 indices_count = data.GetIndicesCount();
  const INativeProcess_Graphics::PrimitiveType primitive_type = data.GetPrimitiveType();
  const Vertex::VertexType vertex_type = data.GetVertexType();
  const T_UINT16 polygon_count = INativeProcess_Graphics::PRIMITIVE_SURF_NUM(primitive_type, indices_count);

  this->vertex_buffer_ = INativeVertexBuffer::Create(vertexes_count, polygon_count, vertex_type);
  void* dest_vertexes;
  this->vertex_buffer_->Lock(&dest_vertexes);
  data.SetupVertex(dest_vertexes);
  this->vertex_buffer_->Unlock();

  this->index_buffer_ = INativeIndexBuffer::Create(indices_count);
  T_UINT16* dest_indices;
  this->index_buffer_->Lock((void**)&dest_indices);
  const T_UINT16* indices = data.GetIndices();
  for (T_UINT16 i = 0; i < indices_count; ++i)
  {
    dest_indices[i] = indices[i];
  }
  this->index_buffer_->Unlock();
}

SubMesh::~SubMesh()
{
  delete this->vertex_buffer_;
  delete this->index_buffer_;
}

void SubMesh::Draw() const
{
  this->vertex_buffer_->SetStreamSource();
  this->index_buffer_->SetIndices();
  this->vertex_buffer_->DrawIndexedPrimitive(this->index_buffer_, INativeProcess_Graphics::PRIMITIVE_TRIANGLES);
}
