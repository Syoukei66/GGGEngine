#include "MeshRenderer.h"
#include "EngineAsset.h"

// =================================================================
// Factory Method
// =================================================================
MeshRenderer* MeshRenderer::Create(const Mesh& mesh, GameObject* entity)
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
