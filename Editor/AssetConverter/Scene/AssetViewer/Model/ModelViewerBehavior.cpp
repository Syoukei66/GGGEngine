#include "ModelViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform3D.h>
#include <Engine/Component/Renderer/MeshRenderer.h>

#include <Entity/Default/Mesh/DefaultMeshAssetEntity.h>
#include <Entity/File/Model/Mesh/ModelMeshAssetEntity.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(ModelViewerBehavior)
{
  this->obj_ = new GameObject3D();
  this->mesh_renderer_ = new MeshRenderer(this->obj_);
  this->obj_->SetRenderer(this->mesh_renderer_);
  return true;
}

GG_DESTRUCT_FUNC_IMPL(ModelViewerBehavior)
{
  delete this->obj_;
  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void ModelViewerBehavior::OnStart(Scene* scene)
{
  scene->AddChild(this->obj_);
}

void ModelViewerBehavior::OnEnd()
{
  this->obj_->RemoveSelf();
}

void ModelViewerBehavior::OnLoad(T_UINT32 unique_id)
{
  const SharedRef<rcModel>& model = AssetManager::Load<rcModel>(unique_id);
  this->mesh_renderer_->SetMesh(model->GetMesh());
  const T_UINT8 material_count = model->GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    this->mesh_renderer_->SetSharedMaterial(model->GetMaterial(i), i);
  }
}

void ModelViewerBehavior::OnUnload()
{
  this->mesh_renderer_->SetMesh(nullptr);
  const T_UINT8 material_count = this->mesh_renderer_->GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    this->mesh_renderer_->SetSharedMaterial(nullptr, i);
  }
}

bool ModelViewerBehavior::IsTarget(T_UINT32 id)
{
  return id == AssetEntity::EntityID::ID_MODEL;
}
