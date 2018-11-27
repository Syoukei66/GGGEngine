#include "ShaderViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform3D.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(ShaderViewerBehavior)
{
  this->obj_ = GameObject3D::Create();
  this->obj_->GetTransform()->RotateX(-Mathf::PI_1_2);
  this->mesh_renderer_ = this->obj_->AddComponent<MeshRenderer>();
  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void ShaderViewerBehavior::OnStart(Scene* scene)
{
  scene->AddChild(this->obj_);
}

void ShaderViewerBehavior::OnEnd()
{
  this->obj_->RemoveSelf();
}

void ShaderViewerBehavior::OnLoad(T_UINT32 unique_id)
{
  this->mesh_renderer_->SetMesh(AssetManager::Load<rcMesh>(DefaultUniqueID::MESH_PLANE));
  this->mesh_renderer_->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_UNLIT));
  this->mesh_renderer_->GetMaterial()->SetShader(AssetManager::Load<rcShader>(unique_id));
}

void ShaderViewerBehavior::OnUnload()
{
  this->mesh_renderer_->SetMesh(nullptr);
  this->mesh_renderer_->SetMaterial(nullptr);
}

bool ShaderViewerBehavior::IsTarget(T_UINT32 id)
{
  return id == AssetEntity::EntityID::ID_SHADER;
}
