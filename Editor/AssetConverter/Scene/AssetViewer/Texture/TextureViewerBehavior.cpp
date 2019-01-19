#include "TextureViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform3D.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(TextureViewerBehavior)
{
  this->obj_ = GameObject3D::Create();
  this->obj_->GetTransform()->RotateX(-Mathf::PI_1_2);
  this->mesh_renderer_ = this->obj_->AddComponent<MeshRenderer>();
  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void TextureViewerBehavior::OnStart(Scene* scene)
{
  scene->AddChild(this->obj_);
}

void TextureViewerBehavior::OnEnd()
{
  this->obj_->RemoveSelf();
}

void TextureViewerBehavior::OnLoad(T_UINT32 unique_id)
{
  this->mesh_renderer_->SetMesh(AssetManager::Load<rcMesh>(DefaultUniqueID::MESH_PLANE));
  this->mesh_renderer_->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_UNLIT));
  this->mesh_renderer_->GetMaterial()->SetMainTexture(AssetManager::Load<rcTexture>(unique_id));
}

void TextureViewerBehavior::OnUnload()
{
  this->mesh_renderer_->SetMesh(nullptr);
  this->mesh_renderer_->SetMaterial(nullptr);
}
