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

MeshRenderer* MeshRenderer::Create(const Mesh* mesh, GameObject* entity)
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
void MeshRenderer::Submit(CommandBuffer* buf) const
{
  if (!this->mesh_)
  {
    return;
  }

  this->SetStreamSource();
  const T_UINT8 material_count = this->materials_.size();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    Material* material = this->materials_[i];
    T_UINT8 pass_count = material->Begin();
    for (T_UINT8 j = 0; j < pass_count; ++j)
    {
      material->BeginPass(j);
      material->SetDefaultProperties(state);
      material->CommitChanges();
      this->DrawSubset(i);
      material->EndPass();
    }
    material->End();
  }
}
