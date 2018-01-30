#include "MeshRenderer.h"

// =================================================================
// Factory Method
// =================================================================
MeshRenderer* MeshRenderer::Create(const Mesh& mesh)
{
  MeshRenderer* ret = new MeshRenderer();
  ret->SetMesh(mesh);
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
MeshRenderer::MeshRenderer()
{
}

// =================================================================
// Method
// =================================================================
void MeshRenderer::EditProperty(T_UINT8 material_index, T_UINT8 pass_index, Material* material)
{
}

void MeshRenderer::DrawSubset(T_UINT8 material_index, T_UINT8 pass_index)
{
  if (!this->mesh_)
  {
    return;
  }
  this->mesh_->DrawSubMesh(material_index);
}
