#include "TextureViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform3D.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(TextureViewerBehavior)
{
  this->obj_ = TestMesh::Create();
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
  const SharedRef<Renderer>& renderer = this->obj_->GetComponent<Renderer>();
  renderer->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_UNLIT)->Clone());
  renderer->GetMaterial()->SetMainTexture(AssetManager::Load<rcTexture>(unique_id));
}

void TextureViewerBehavior::OnUnload()
{
}

void TextureViewerBehavior::OnUpdate()
{
  this->obj_->EditWithImGUI();
}
