#include "MaterialAssetConverterSetting.h"

// =================================================================
// Methods from ConverterSetting
// =================================================================
bool MaterialAssetConverterSetting::EditWithImGuiProcess()
{
  using namespace Shader;
  bool reload = false;
  for (const auto& pair : this->edit_data_.property_table_)
  {
    const std::string& name = pair.first;
    const MaterialPropertyData& data = pair.second;
    const MaterialPropertyType type = static_cast<MaterialPropertyType>(data.type_);
    unsigned char* p = &this->edit_data_.data_[data.offset_];
    switch (type)
    {
    case MaterialPropertyType::kBool:
      this->is_updated_ |= ImGui::Checkbox(name.c_str(), (bool*)p);
      break;
    case MaterialPropertyType::kInt:
      this->is_updated_ |= ImGui::DragInt(name.c_str(), (int*)p);
      break;
    case MaterialPropertyType::kUint:
      this->is_updated_ |= ImGui::DragInt(name.c_str(), (int*)p);
      break;
    case MaterialPropertyType::kFloat:
      this->is_updated_ |= ImGui::DragFloat(name.c_str(), (float*)p, 0.01f);
      break;
    case MaterialPropertyType::kColor:
      this->is_updated_ |= ImGui::ColorEdit4(name.c_str(), ((TColor*)p)->data);
      break;
    case MaterialPropertyType::kTexture:
      //this->is_updated_ |= ImGui::Checkbox(name.c_str(), (bool*)p);
      break;
    case MaterialPropertyType::DATANUM:
      break;
    }
  }
  if (ImGui::Button(u8"�K�p"))
  {
    this->is_master_ = true;
    reload = true;
  }
  return reload;
}

void MaterialAssetConverterSetting::StoreShaderProperties(const MaterialData& data)
{
  using namespace Shader;

  const SharedRef<rcShader>& shader = AssetManager::Load<rcShader>(data.shader_unique_id_);
  // �V�F�[�_�[����擾�����f�[�^�����MaterialData����蒼��
  MaterialData old_data = this->is_master_ ? this->edit_data_ : data;
  this->edit_data_ = MaterialData();
  MaterialData::CreateWithShader(shader, &this->edit_data_);
  // �Â��f�[�^�ɓ����v���p�e�B������΂��̂܂܎g�p����
  this->edit_data_.main_texture_unique_id_ = old_data.main_texture_unique_id_;
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
    
    // �e�N�X�`���̏ꍇ
    if (type == MaterialPropertyType::kTexture)
    {
      this->edit_data_.textures_[new_p.offset_] = old_data.textures_[old_p.offset_];
      continue;
    }
    
    // ����ȊO�̏ꍇ
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
}
