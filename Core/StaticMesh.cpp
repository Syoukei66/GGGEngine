#include "StaticMesh.h"

// =================================================================
// Constructor / Destructor
// =================================================================
rcStaticMesh* rcStaticMesh::Create(rcVertexBuffer* vertex_buffer, rcIndexBuffer** index_buffers, T_UINT8 submesh_count, Graphics::PrimitiveType primitive_type)
{
  rcStaticMesh* ret = new rcStaticMesh(vertex_buffer, index_buffers, submesh_count, primitive_type);
  ret->Resource::Init();
  return ret;
}

rcStaticMesh::rcStaticMesh(rcVertexBuffer* vertex_buffer, rcIndexBuffer** index_buffers, T_UINT8 submesh_count, Graphics::PrimitiveType primitive_type)
{
  this->vertex_buffer_ = vertex_buffer;
  this->index_buffers_ = index_buffers;
  this->submesh_count_ = submesh_count;
  this->primitive_type_ = primitive_type;
  this->vertex_buffer_->Retain();
  for (T_UINT32 i = 0; i < this->primitive_type_; ++i)
  {
    this->index_buffers_[i]->Retain();
  }
}

rcStaticMesh::~rcStaticMesh()
{
  this->vertex_buffer_->Release();
  for (T_UINT32 i = 0; i < this->primitive_type_; ++i)
  {
    this->index_buffers_[i]->Release();
  }
}

