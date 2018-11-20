#include "MeshRenderer.h"
#include <Asset/Mesh/Mesh.h>

// =================================================================
// Factory Method
// =================================================================
MeshRenderer* MeshRenderer::Create(const SharedRef<const rcMesh>& mesh, const SharedRef<GameObject>& entity)
{
  MeshRenderer* ret = new MeshRenderer(entity);
  ret->SetMesh(mesh);
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
MeshRenderer::MeshRenderer(const SharedRef<GameObject>& entity)
  : Renderer(entity)
  , mesh_()
  , submesh_visible_()
{
}

MeshRenderer::~MeshRenderer()
{
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
