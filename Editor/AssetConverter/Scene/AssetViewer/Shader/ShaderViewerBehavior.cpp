#include "ShaderViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform3D.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(ShaderViewerBehavior)
{
  this->obj_ = TestMesh::Create();  return true;
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
  //const SharedRef<AssetEntity>& entity = this->GetEntity();
  //MaterialAssetConverterSetting* setting = static_cast<MaterialAssetConverterSetting*>(entity->GetMetaData()->GetConverterSetting().get());
  //setting->StoreShaderProperties(*entity->GetData<MaterialData>());

  const SharedRef<Renderer>& renderer = this->obj_->GetComponent<Renderer>();
  //this->material_ = rcMaterial::Create(setting->edit_data_);
  //renderer->SetMaterial(this->material_);
}

void ShaderViewerBehavior::OnUnload()
{
}

void ShaderViewerBehavior::OnUpdate()
{
  this->obj_->EditWithImGUI();
}
