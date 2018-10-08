#include "MeshRenderer.h"

// =================================================================
// Factory Method
// =================================================================
MeshRenderer* MeshRenderer::Create(const rcMesh* mesh, GameObject* entity)
{
  MeshRenderer* ret = new MeshRenderer(entity);
  ret->SetMesh(mesh);
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
MeshRenderer::MeshRenderer(GameObject* entity)
  : Renderer(entity)
{
}

// =================================================================
// Method
// =================================================================
bool MeshRenderer::SetStreamSource() const
{
  if (!this->mesh_)
  {
    return false;
  }
  this->mesh_->SetStreamSource();
  return true;
}

void MeshRenderer::SetProperties(rcShader* shader) const
{
}

void MeshRenderer::DrawSubset(T_UINT8 submesh_index) const
{
  this->mesh_->DrawSubset(submesh_index);
}
