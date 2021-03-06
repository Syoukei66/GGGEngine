#include "MaterialEditView.h"
#include <Entity/AssetEntity.h>

// =================================================================
// Constructor / Destructor
// =================================================================
MaterialEditView::MaterialEditView()
  : material_()
  , is_master_()
  , is_updated_()
  , edit_data_map_()
  , texture_select_scene_(TextureSelectScene::Create())
{
}

MaterialEditView::~MaterialEditView()
{
  this->texture_select_scene_->End();
}

// =================================================================
// Methods
// =================================================================
SharedRef<rcMaterial> MaterialEditView::CreateEditMaterial(const MaterialData& data)
{
  using namespace Shader;

  // シェーダー切り替え時にデータが失われないように
  if (this->material_)
  {
    this->edit_data_map_[this->material_->GetShader()->GetShaderName()] = this->edit_data_;
  }

  const SharedRef<rcShader>& shader = AssetManager::Load<rcShader>(data.shader_unique_id_);

  // シェーダーから取得したデータを基にMaterialDataを作り直す
  const MaterialData& old_data = this->is_master_ ? this->edit_data_map_[shader->GetShaderName()] : data;
  this->edit_data_ = MaterialData();
  MaterialData::CreateWithShader(shader->GetPropertyData(), shader->GetUniqueId(), &this->edit_data_);
  // 古いデータに同じプロパティがあればそのまま使用する
  for (const auto& pair : old_data.property_table_)
  {
    const std::string& name = pair.first;
    const auto& itr = this->edit_data_.property_table_.find(name);
    if (itr == this->edit_data_.property_table_.end())
    {
      continue;
    }
    const MaterialPropertyData& old_p = pair.second;
    const MaterialPropertyData& new_p = itr->second;
    const MaterialPropertyType type = static_cast<MaterialPropertyType>(old_p.type_);

    // テクスチャの場合
    if (type == MaterialPropertyType::kTexture)
    {
      this->edit_data_.textures_[new_p.offset_] = old_data.textures_[old_p.offset_];
      continue;
    }

    // それ以外の場合
    const T_UINT32 size = GetMaterialPropertySize(type);
    if (itr != this->edit_data_.property_table_.end())
    {
      for (T_UINT32 i = 0; i < new_p.count_; ++i)
      {
        const T_UINT32 new_offset = new_p.offset_ + i * size;
        const T_UINT32 olf_offset = old_p.offset_ + i * size;
        for (T_UINT32 j = 0; j < size; ++j)
        {
          this->edit_data_.data_[new_offset + j] = old_data.data_[olf_offset + j];
        }
      }
    }
  }

  // View用のデータ作成
  this->edit_property_datas_.clear();
  for (const auto& pair : this->edit_data_.property_table_)
  {
    this->edit_property_datas_[pair.second.index_] = &this->edit_data_.property_table_[pair.first];
  }

  this->material_ = rcMaterial::Create(this->edit_data_);
  return this->material_;
}

bool MaterialEditView::EditWithImGui(AssetConverterContext* context)
{
  using namespace Shader;
  bool reload = false;

  const ShaderData* shader = context->GetEntity(this->edit_data_.shader_unique_id_)->GetData<ShaderData>();
  for (const auto& pair : this->edit_property_datas_)
  {
    const MaterialPropertyData& data = *pair.second;
    const std::string& name = data.name_;
    const MaterialPropertyType type = static_cast<MaterialPropertyType>(data.type_);

    ImGui::PushID(data.index_);
    if (type == MaterialPropertyType::kTexture)
    {
      const T_UINT32 texture_unique_id = this->edit_data_.textures_[data.offset_];
      const std::string& filename = "(" + context->GetEntity(texture_unique_id)->GetMetaData()->GetURI().GetFileName() + ")";
      const SharedRef<rcTexture>& texture = AssetManager::Load<rcTexture>(texture_unique_id);
      if (ImGui::ImageButton(texture->GetTextureView()->GetImTextureID(), ImVec2(16, 16)))
      {
        this->texture_select_scene_->Run(texture, [&, data](const SharedRef<rcTexture>& texture)
        {
          this->edit_data_.textures_.at(data.offset_) = texture->GetUniqueId();
          this->is_updated_ = true;
          this->is_master_ = true;
        });
      }
      ImGui::SameLine();
      ImGui::AlignFirstTextHeightToWidgets();
      ImGui::Text(filename.c_str());
      ImGui::SameLine();
      ImGui::Text(name.c_str());
    }
    // VectorPropertyの時の処理
    else if (data.count_ > 1)
    {
      unsigned char* p = &this->edit_data_.data_[data.offset_];
      if (type == MaterialPropertyType::kInt)
      {
        this->is_updated_ |= ImGui::DragInt4(name.c_str(), (int*)p);
      }
      else if (type == MaterialPropertyType::kUint)
      {
        this->is_updated_ |= ImGui::DragInt4(name.c_str(), (int*)p);
      }
      else if (type == MaterialPropertyType::kFloat)
      {
        this->is_updated_ |= ImGui::DragFloat4(name.c_str(), (float*)p, 0.01f);
      }
    }
    else
    {
      unsigned char* p = &this->edit_data_.data_[data.offset_];
      if (type == MaterialPropertyType::kBool)
      {
        this->is_updated_ |= ImGui::Checkbox(name.c_str(), (bool*)p);
      }
      if (type == MaterialPropertyType::kInt)
      {
        this->is_updated_ |= ImGui::DragInt(name.c_str(), (int*)p);
      }
      else if (type == MaterialPropertyType::kUint)
      {
        this->is_updated_ |= ImGui::DragInt(name.c_str(), (int*)p);
      }
      else if (type == MaterialPropertyType::kFloat)
      {
        this->is_updated_ |= ImGui::DragFloat(name.c_str(), (float*)p, 0.01f);
      }
      else if (type == MaterialPropertyType::kColor)
      {
        this->is_updated_ |= ImGui::ColorEdit4(name.c_str(), ((TColor*)p)->data);
      }
    }
    ImGui::PopID();
  }
  if (this->is_updated_)
  {
    this->is_master_ = true;
  }
  if (ImGui::Button(u8"適用"))
  {
    reload = true;
  }
  return reload;
}

void MaterialEditView::Update()
{
  using namespace Shader;
  if (!this->is_updated_)
  {
    return;
  }
  const MaterialData* data = &this->edit_data_;
  for (const auto& pair : data->property_table_)
  {
    const MaterialPropertyData& p = pair.second;
    const std::string& name = pair.first;
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
      this->material_->SetTexture(name, AssetManager::Load<rcTexture>(data->textures_[data->property_table_.at(name).offset_]));
      break;
    case MaterialPropertyType::DATANUM:
      break;
    }
  }
  this->material_->CommitChanges();
  this->is_updated_ = false;
}

void MaterialEditView::Reload(AssetViewerBehavior* behavior, AssetConverterContext* context)
{
  this->texture_select_scene_->Reload(behavior, context);
}
