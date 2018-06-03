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
void MeshRenderer::Draw(GameObjectRenderState* state)
{
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
      this->DrawSubset(i, j);
      material->EndPass();
    }
    material->End();
  }
}

void MeshRenderer::SetStreamSource()
{
  if (!this->mesh_)
  {
    return;
  }
  this->mesh_->SetStreamSource();
}

void MeshRenderer::DrawSubset(T_UINT8 material_index, T_UINT8 pass_index)
{
  if (!this->mesh_)
  {
    return;
  }
  this->mesh_->DrawSubset(material_index);
}
