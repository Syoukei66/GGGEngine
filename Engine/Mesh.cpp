#include "Mesh.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Mesh::Mesh()
  : orginal_(nullptr)
  , sub_meshes_()
{}

Mesh::Mesh(const MeshData& data)
  : orginal_(nullptr)
  , sub_meshes_()
{
  this->AddSubMesh(data.CreateSubMesh());
}

Mesh::~Mesh()
{
}

Mesh* Mesh::Clone()
{
  Mesh* clone = new Mesh();
  clone->orginal_ = this;
  for (SubMesh* sub_mesh : this->sub_meshes_)
  {
    clone->AddSubMesh(sub_mesh->Clone());
  }
  return clone;
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
