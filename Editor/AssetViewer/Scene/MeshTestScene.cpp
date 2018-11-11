#include "MeshTestScene.h"

// =================================================================
// Methods from Scene
// =================================================================
void MeshTestScene::OnLoad()
{
  this->camera_ = new Camera3D_LookAt();
  this->camera_->GetTransform()->SetZ(-10.0f);
  this->AddCamera(this->camera_);

  this->obj_ = new GameObject3D();
  this->obj_->GetTransform()->RotateX(Mathf::PI_1_2);
  MeshRenderer* renderer = MeshRenderer::Create(Asset::ModelMesh::CYLINDER, this->obj_);
  renderer->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_LAMBERT));
  this->obj_->SetRenderer(renderer);
  this->AddChild(this->obj_);
}

void MeshTestScene::OnUnload()
{
  delete this->obj_;
  delete this->camera_;
}

void MeshTestScene::OnShow(ISceneShowListener* listener)
{
}

void MeshTestScene::OnHide(ISceneHideListener* listener)
{
}
