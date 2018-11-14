#include "MeshViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform3D.h>
#include <Engine/Component/Renderer/MeshRenderer.h>

#include <Entity/Default/Mesh/DefaultMeshAssetEntity.h>
#include <Entity/File/Model/Mesh/ModelMeshAssetEntity.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(MeshViewerBehavior)
{
  this->obj_ = new GameObject3D();
  this->mesh_renderer_ = new MeshRenderer(this->obj_);
  this->obj_->SetRenderer(this->mesh_renderer_);
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
void MeshViewerBehavior::OnStart(Scene* scene)
{
  scene->AddChild(this->obj_);
}

void MeshViewerBehavior::OnEnd()
{
  this->obj_->RemoveSelf();
}

void MeshViewerBehavior::OnLoad(T_UINT32 unique_id)
{
  this->mesh_renderer_->SetMesh(AssetManager::Load<rcMesh>(unique_id));
  this->mesh_renderer_->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_LAMBERT));
}

void MeshViewerBehavior::OnUnload()
{
  this->mesh_renderer_->SetMesh(nullptr);
  this->mesh_renderer_->SetMaterial(nullptr);
}

bool MeshViewerBehavior::IsTarget(T_UINT32 id)
{
  return id == AssetEntity::EntityID::ID_DEFAULT_MESH || id == AssetEntity::EntityID::ID_MODEL_MESH;
}
