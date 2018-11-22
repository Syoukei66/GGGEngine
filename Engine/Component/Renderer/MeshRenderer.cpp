#include "MeshRenderer.h"
#include <Asset/Mesh/Mesh.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(MeshRenderer, GameObject* obj)
{
  return Renderer::Init(obj);
}

// =================================================================
// Methods
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

void MeshRenderer::SetProperties(const SharedRef<rcShader>& shader) const
{
}

void MeshRenderer::DrawSubset(T_UINT8 submesh_index) const
{
  if (!this->GetSubmeshVisible(submesh_index))
  {
    return;
  }
  this->mesh_->DrawSubset(submesh_index);
}
