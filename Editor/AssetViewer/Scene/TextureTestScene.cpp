#include "TextureTestScene.h"

// =================================================================
// Methods from Scene
// =================================================================
void TextureTestScene::OnLoad()
{
  this->camera_ = new Camera2D();
  this->AddCamera(this->camera_);

  this->obj_ = new GameObject2D();
  const SharedRef<rcMesh>& mesh = AssetManager::GetLoader<rcMesh>(DefaultUniqueID::MESH_PLANE);
  MeshRenderer* renderer = MeshRenderer::Create(mesh, this->obj_);
  this->obj_->SetRenderer(renderer);
  this->AddChild(this->obj_);
}

void TextureTestScene::OnUnload()
{
  delete this->obj_;
  delete this->camera_;
}

void TextureTestScene::OnShow(ISceneShowListener* listener)
{
}

void TextureTestScene::OnHide(ISceneHideListener* listener)
{
}
