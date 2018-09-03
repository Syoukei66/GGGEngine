#include "StaticMesh.h"

// =================================================================
// Factory Method
// =================================================================
rcStaticMesh* rcStaticMesh::Create(rcVertexBuffer* vertex_buffer, rcIndexBuffer** index_buffers, T_UINT8 submesh_count, Graphics::PrimitiveType primitive_type)
{
  rcStaticMesh* ret = new rcStaticMesh(vertex_buffer, index_buffers, submesh_count, primitive_type);
  ret->Resource::Init();
  return ret;
}

rcStaticMesh* rcStaticMesh::Create(const StaticMeshData& data)
{
  //Vertex Buffer
  rcVertexBuffer* vertex_buffer = rcVertexBuffer::Create(data.vertex_count_, data.polygon_count_, data.vertex_format_);
  unsigned char* p;
  vertex_buffer->Lock((void**)&p);
  const T_UINT64 byte_count = data.vertex_count_ * data.vertex_size_;
  for (T_UINT64 i = 0; i < byte_count; ++i)
  {
    p[i] = data.data_[i];
  }
  vertex_buffer->Unlock();

  //Index Buffers
  rcIndexBuffer** index_buffers = new rcIndexBuffer*[data.submesh_count_];
  for (T_UINT32 i = 0, ii = 0; i < data.submesh_count_; ++i)
  {
    T_UINT32* index_data;
    index_buffers[i] = rcIndexBuffer::Create(data.submesh_index_counts_[i]);
    index_buffers[i]->Lock((void**)&index_data);
    for (T_UINT32 j = 0; j < data.submesh_index_counts_[i]; ++j)
    {
      index_data[j] = data.indices_[ii + j];
    }
    index_buffers[i]->Unlock();
    ii += data.submesh_index_counts_[i];
  }

  rcStaticMesh* ret = Create(vertex_buffer, index_buffers, data.submesh_count_);

  vertex_buffer->Release();
  for (T_UINT32 i = 0; i < data.submesh_count_; ++i)
  {
    index_buffers[i]->Release();
  }

  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
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

