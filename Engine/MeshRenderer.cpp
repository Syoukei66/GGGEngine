#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::~MeshRenderer()
{
}

// =================================================================
// Method
// =================================================================
void MeshRenderer::Draw(GameObjectRenderState* state)
{
  const T_UINT8 material_count = this->materials_.size();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    Material* material = this->materials_[i];
    T_UINT8 pass_count = material->Begin();
    for (T_UINT8 j = 0; j < pass_count; ++j)
    {
      material->BeginPass(j);
      material->CommitChanges();
      material->SetWorldMatrix(state);
      this->mesh_->DrawSubset(i);
      material->EndPass();
    }
    material->End();
  }
}
