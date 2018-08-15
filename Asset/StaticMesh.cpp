#include "StaticMesh.h"

StaticMesh::StaticMesh(INativeVertexBuffer* vertex_buffer, INativeIndexBuffer** index_buffers, T_UINT8 submesh_count)
  : vertex_buffer_(vertex_buffer)
  , index_buffers_(index_buffers)
  , submesh_count_(submesh_count)
{
}

StaticMesh::~StaticMesh()
{
}

Mesh* StaticMesh::CloneDynamic(bool source_delete)
{
  return nullptr;
}

void StaticMesh::SetStreamSource() const
{
}

void StaticMesh::DrawSubset(T_UINT8 index) const
{
}
