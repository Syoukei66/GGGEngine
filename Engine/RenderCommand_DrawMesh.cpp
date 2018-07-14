#include "RenderCommand_DrawMesh.h"


void RenderCommand_DrawMesh::Render(RenderState* state)
{
  const Mesh* mesh = this->mesh_renderer_->GetMesh();
  if (!mesh)
  {
    return;
  }

  mesh->SetStreamSource();
  const T_UINT8 material_count = this->mesh_renderer_->GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    Material* material = this->mesh_renderer_->GetMaterial(i);
    T_UINT8 pass_count = material->Begin();
    for (T_UINT8 j = 0; j < pass_count; ++j)
    {
      material->BeginPass(j);
      material->SetDefaultProperties(state);
      material->CommitChanges();
      mesh->DrawSubset(i);
      material->EndPass();
    }
    material->End();
  }
}
