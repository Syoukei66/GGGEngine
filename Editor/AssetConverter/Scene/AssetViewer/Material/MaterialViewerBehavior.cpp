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
  setting->StoreShaderProperties(*entity->GetData<MaterialData>());

  const SharedRef<Renderer>& renderer = this->obj_->GetComponent<Renderer>();
  this->material_ = AssetManager::Load<rcMaterial>(unique_id)->Clone();
  renderer->SetMaterial(this->material_);
}

void MaterialViewerBehavior::OnUnload()
{
}

void MaterialViewerBehavior::OnUpdate()
{
  using namespace Shader;
  this->obj_->EditWithImGUI();
  MaterialAssetConverterSetting* setting = static_cast<MaterialAssetConverterSetting*>(this->GetEntity()->GetMetaData()->GetConverterSetting().get());
  if (!setting->is_updated_)
  {
    return;
  }
  const MaterialData* data = &setting->edit_data_;
  for (const auto& pair : data->property_table_)
  {
    const std::string& name = pair.first;
    const MaterialPropertyData& p = pair.second;
    const MaterialPropertyType type = static_cast<MaterialPropertyType>(p.type_);
    switch (type)
    {
    case MaterialPropertyType::kBool:
      this->SetMaterialProperty<bool>(name, p.count_, p.offset_, GetMaterialPropertySize(type), data);
      break;
    case MaterialPropertyType::kInt:
      this->SetMaterialProperty<T_FIXED_INT32>(name, p.count_, p.offset_, GetMaterialPropertySize(type), data);
      break;
    case MaterialPropertyType::kUint:
      this->SetMaterialProperty<T_FIXED_UINT32>(name, p.count_, p.offset_, GetMaterialPropertySize(type), data);
      break;
    case MaterialPropertyType::kFloat:
      this->SetMaterialProperty<T_FIXED_FLOAT>(name, p.count_, p.offset_, GetMaterialPropertySize(type), data);
      break;
    case MaterialPropertyType::kColor:
      this->SetMaterialProperty<TColor>(name, p.count_, p.offset_, GetMaterialPropertySize(type), data);
      break;
    case MaterialPropertyType::kTexture:
      this->material_->GetTexture(name) = AssetManager::Load<rcTexture>(data->textures_[data->property_table_.at(name).offset_]);
      break;
    case MaterialPropertyType::DATANUM:
      break;
    }
  }
  this->material_->CommitChanges();
  setting->is_updated_ = false;
}
