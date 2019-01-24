#include "MaterialViewerBehavior.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(MaterialViewerBehavior)
{
  this->obj_ = TestMesh::Create();
  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void MaterialViewerBehavior::OnStart(Scene* scene)
{
  scene->AddChild(this->obj_);
}

void MaterialViewerBehavior::OnEnd()
{
  this->obj_->RemoveSelf();
}

void MaterialViewerBehavior::OnLoad(T_UINT32 unique_id)
{
  const SharedRef<Renderer>& renderer = this->obj_->GetComponent<Renderer>();
  renderer->SetMaterial(AssetManager::Load<rcMaterial>(unique_id));
}

void MaterialViewerBehavior::OnUnload()
{
}

void MaterialViewerBehavior::OnUpdate()
{
  this->obj_->EditWithImGUI();
}
