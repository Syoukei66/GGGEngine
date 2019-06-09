#include "StaticMeshViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform.h>

// =================================================================
// GGG Statement
// =================================================================
GG_CREATE_FUNC_IMPL(StaticMeshViewerBehavior)
{
  this->obj_ = GameObject::Create();
  this->mesh_renderer_ = this->obj_->AddComponent<MeshRenderer>();
  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void StaticMeshViewerBehavior::OnStart(Scene* scene)
{
  scene->AddChild(this->obj_);
}

void StaticMeshViewerBehavior::OnEnd()
{
  this->obj_->RemoveSelf();
}

void StaticMeshViewerBehavior::OnLoad(T_UINT32 unique_id, AssetConverterContext* context)
{
  this->mesh_renderer_->SetMesh(AssetManager::Load<rcMesh>(unique_id));
  const T_UINT32 submesh_count = this->mesh_renderer_->GetMesh()->GetSubmeshCount();
  for (T_UINT32 i = 0; i < submesh_count; ++i)
  {
    this->mesh_renderer_->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_LAMBERT), i);
    //this->mesh_renderer_->GetMaterial(i)->SetMainTexture(AssetManager::Load<rcTexture>(DefaultUniqueID::TEXTURE_WHITE));
  }
}

void StaticMeshViewerBehavior::OnUnload()
{
  this->mesh_renderer_->SetMesh(nullptr);
  this->mesh_renderer_->SetMaterial(nullptr);
}
