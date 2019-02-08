#include "MaterialViewerBehavior.h"
#include <Entity/File/Material/MaterialAssetConverterSetting.h>

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
  const SharedRef<AssetEntity>& entity = this->GetEntity();
  MaterialAssetConverterSetting* setting = static_cast<MaterialAssetConverterSetting*>(entity->GetMetaData()->GetConverterSetting().get());
  const SharedRef<Renderer>& renderer = this->obj_->GetComponent<Renderer>();
  renderer->SetMaterial(setting->editor.CreateEditMaterial(*entity->GetData<MaterialData>()));
}

void MaterialViewerBehavior::OnUnload()
{
}

void MaterialViewerBehavior::OnUpdate()
{
  this->obj_->EditWithImGUI();
  MaterialAssetConverterSetting* setting = static_cast<MaterialAssetConverterSetting*>(this->GetEntity()->GetMetaData()->GetConverterSetting().get());
  setting->editor.Update();
}
