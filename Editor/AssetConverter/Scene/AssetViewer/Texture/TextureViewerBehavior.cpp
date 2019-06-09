#include "TextureViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform.h>

// =================================================================
// GGG Statement
// =================================================================
GG_CREATE_FUNC_IMPL(TextureViewerBehavior)
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

void TextureViewerBehavior::OnLoad(T_UINT32 unique_id, AssetConverterContext* context)
{
  const SharedRef<Renderer>& renderer = this->obj_->GetComponent<Renderer>();
  renderer->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_UNLIT)->Clone());
  renderer->GetMaterial()->SetTexture(Shader::MAIN_TEXTURE_NAME, AssetManager::Load<rcTexture>(unique_id));
}

void TextureViewerBehavior::OnUnload()
{
}

void TextureViewerBehavior::OnUpdate(const ActivityContext& activity_context, AssetConverterContext* context)
{
  this->obj_->EditWithImGUI(activity_context);
}
