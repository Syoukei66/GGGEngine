#include "MeshData.h"

// =================================================================
// Constructor / Destructor
// =================================================================
MeshData::MeshData()
  : instances_()
{
}

MeshData::~MeshData()
{
  for (Mesh* mesh : this->instances_)
  {
    delete mesh;
  }
}

// =================================================================
// Method
// =================================================================
Mesh* MeshData::CreateMesh() const
{
  Mesh* ret = new Mesh();

  const T_UINT32 vertex_count = this->GetVertexCount();
  const T_UINT32 index_count = this->GetIndexCount();
  const INativeProcess_Graphics::PrimitiveType primitive_type = this->GetPrimitiveType();
  const T_UINT32 vertex_format = this->GetVertexFormat();
  const T_UINT16 polygon_count = INativeProcess_Graphics::PRIMITIVE_SURF_NUM(primitive_type, index_count);

  ret->CreateVertices(vertex_count, polygon_count, vertex_format, primitive_type);
  ret->CreateIndices(index_count);
  this->SetupMesh(ret);
  ret->CommitChanges();
  
  const_cast<MeshData*>(this)->instances_.push_back(ret);
  return ret;
}

