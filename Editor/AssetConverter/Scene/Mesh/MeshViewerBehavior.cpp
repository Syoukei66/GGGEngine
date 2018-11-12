#include "MeshViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform3D.h>
#include <Engine/Component/Renderer/MeshRenderer.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(MeshViewerBehavior)
{
  this->obj_ = new GameObject3D();
  return true;
}

GG_DESTRUCT_FUNC_IMPL(MeshViewerBehavior)
{
  delete this->obj_;
  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void MeshViewerBehavior::OnStart(const MeshData* data, Scene* scene)
{
  this->obj_->GetTransform()->RotateX(Mathf::PI_1_2);
  MeshRenderer* renderer = MeshRenderer::Create(rcMesh::Create(*data), this->obj_);
  renderer->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_LAMBERT));
  this->obj_->SetRenderer(renderer);
  scene->AddChild(this->obj_);
}

void MeshViewerBehavior::OnEnd()
{
  this->obj_->RemoveSelf();
}
