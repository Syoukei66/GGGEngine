#include "Mesh.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Mesh::Mesh()
  : sub_meshes_()
{}

Mesh::Mesh(const MeshData& data)
  : sub_meshes_()
{
  this->AddSubMesh(data.CreateSubMesh());
}

Mesh::~Mesh()
{
}

// =================================================================
// Method
// =================================================================
void Mesh::AddSubMesh(SubMesh* mesh)
{
  this->sub_meshes_.push_back(mesh);
}

void Mesh::DrawSubMesh(T_UINT16 index) const
{
  if (index >= this->sub_meshes_.size())
  {
    return;
  }
  this->sub_meshes_[index]->Draw();
}
