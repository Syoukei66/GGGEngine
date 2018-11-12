#include "TextureViewScene.h"
#include <Engine/Component/Renderer/MeshRenderer.h>

// =================================================================
// Methods from Scene
// =================================================================
void TextureViewScene::OnLoad()
{
  this->camera_3d_ = new Camera2D();
  this->AddCamera(this->camera_3d_);

  this->obj_ = new GameObject2D();
  const SharedRef<rcMesh>& mesh = AssetManager::GetLoader<rcMesh>(DefaultUniqueID::MESH_PLANE);
  MeshRenderer* renderer = MeshRenderer::Create(mesh, this->obj_);
  this->obj_->SetRenderer(renderer);
  this->AddChild(this->obj_);
}

void TextureViewScene::OnUnload()
{
  delete this->obj_;
  delete this->camera_3d_;
}

void TextureViewScene::OnShow(ISceneShowListener* listener)
{
}

void TextureViewScene::OnHide(ISceneHideListener* listener)
{
}
