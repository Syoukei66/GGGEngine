#include "MeshData.h"

// =================================================================
// Constructor / Destructor
// =================================================================
MeshData::MeshData()
{
}

MeshData::~MeshData()
{
  for (SubMesh* mesh : this->instances_)
  {
    delete mesh;
  }
}

// =================================================================
// Method
// =================================================================
SubMesh* MeshData::CreateSubMesh() const
{
  SubMesh* ret = new SubMesh(*this);
  const_cast<MeshData*>(this)->instances_.push_back(ret);
  return ret;
}
