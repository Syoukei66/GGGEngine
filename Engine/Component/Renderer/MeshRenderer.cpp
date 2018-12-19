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

bool MeshRenderer::BeginPass(T_UINT8 pass, const SharedRef<rcShader>& shader) const
{
  if (!this->mesh_)
  {
    return false;
  }
  shader->BeginPass(pass, this->mesh_->GetVertexDeclaration());
  return true;
}

void MeshRenderer::DrawSubset(T_UINT8 submesh_index) const
{
  if (!this->GetSubmeshVisible(submesh_index))
  {
    return;
  }
  this->mesh_->DrawSubset(submesh_index);
}
