#include "MeshData.h"
#include "SubMesh.h"

// =================================================================
// Constructor / Destructor
// =================================================================
MeshData::MeshData()
  : instances_()
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
