#include "Mesh.h"

Mesh* Mesh::CreateWithMeshData(const MeshData& data)
{
  Mesh* ret = new Mesh();
  ret->AddSubset(data.CreateSubMesh());
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
Mesh::Mesh()
  : sub_meshes_()
{}

Mesh::~Mesh()
{
}

// =================================================================
// Method
// =================================================================
void Mesh::AddSubset(SubMesh* mesh)
{
  this->sub_meshes_.push_back(mesh);
}

void Mesh::DrawSubset(T_UINT16 index) const
{
  this->sub_meshes_[index]->Draw();
}
