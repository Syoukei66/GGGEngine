#include "DynamicMeshViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform3D.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(DynamicMeshViewerBehavior)
{
  this->obj_ = GameObject3D::Create();
  this->mesh_renderer_ = this->obj_->AddComponent<MeshRenderer>();
  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void DynamicMeshViewerBehavior::OnStart(Scene* scene)
{
  scene->AddChild(this->obj_);
}

void DynamicMeshViewerBehavior::OnEnd()
{
  this->obj_->RemoveSelf();
}

void DynamicMeshViewerBehavior::OnLoad(T_UINT32 unique_id)
{
  SharedRef<rcDynamicMesh> mesh = AssetManager::Load<rcDynamicMesh>(unique_id);
  mesh->CommitChanges();
  this->mesh_renderer_->SetMesh(mesh);
  const T_UINT32 submesh_count = this->mesh_renderer_->GetMesh()->GetSubmeshCount();
  for (T_UINT32 i = 0; i < submesh_count; ++i)
  {
    this->mesh_renderer_->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_LAMBERT), i);
    this->mesh_renderer_->GetMaterial(i)->SetMainTexture(AssetManager::Load<rcTexture>(DefaultUniqueID::TEXTURE_WHITE));
  }
}

void DynamicMeshViewerBehavior::OnUnload()
{
  this->mesh_renderer_->SetMesh(nullptr);
  this->mesh_renderer_->SetMaterial(nullptr);
}

bool DynamicMeshViewerBehavior::IsTarget(T_UINT32 id)
{
  return id == AssetEntity::EntityID::ID_MODEL_DYNAMIC_MESH;
}
