#include "TextureViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform3D.h>
#include <Engine/Component/Renderer/MeshRenderer.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(TextureViewerBehavior)
{
  this->obj_ = new GameObject3D();
  this->mesh_renderer_ = new MeshRenderer(this->obj_);
  this->obj_->SetRenderer(this->mesh_renderer_);
  return true;
}

GG_DESTRUCT_FUNC_IMPL(TextureViewerBehavior)
{
  delete this->obj_;
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
  this->mesh_renderer_->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::SHADER_FLAT));
  this->mesh_renderer_->GetMaterial()->SetMainTexture(AssetManager::Load<rcTexture>(DefaultUniqueID::TEXTURE_WHITE));
}

void TextureViewerBehavior::OnUnload()
{
  this->mesh_renderer_->SetMesh(nullptr);
  this->mesh_renderer_->SetMaterial(nullptr);
}

bool TextureViewerBehavior::IsTarget(T_UINT32 id)
{
  return id == AssetEntity::EntityID::ID_TEXTURE;
}
