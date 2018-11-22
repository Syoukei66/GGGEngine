#include "TextureViewScene.h"
#include <Engine/Component/Renderer/MeshRenderer.h>

// =================================================================
// Methods from Scene
// =================================================================
void TextureViewScene::OnLoad()
{
  this->camera_ = GameObject2D::Create();
  this->AddCamera(this->camera_->GetComponent<Camera>());

  this->obj_ = GameObject2D::Create();
  const SharedRef<rcMesh>& mesh = AssetManager::GetLoader<rcMesh>(DefaultUniqueID::MESH_PLANE);
  const SharedRef<MeshRenderer>& renderer = this->obj_->AddComponent<MeshRenderer>();
  renderer->SetMesh(mesh);
  this->AddChild(this->obj_);
}

void TextureViewScene::OnUnload()
{
  this->obj_ = nullptr;
  this->camera_ = nullptr;
}

void TextureViewScene::OnShow()
{
}

void TextureViewScene::OnHide()
{
}
