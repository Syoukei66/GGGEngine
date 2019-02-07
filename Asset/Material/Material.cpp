#include "Material.h"

#include <Asset/Shader/Shader.h>

// =================================================================
// CreateFunction(MaterialData)
// =================================================================
void MaterialData::CreateWithShader(const SharedRef<rcShader>& shader, MaterialData* dest)
{
  dest->shader_unique_id_ = shader->GetUniqueId();
  dest->data_.resize(shader->GetBufferSize());

  using namespace Shader;

  T_UINT32 data_offset = 0;
  for (const ScalaPropertyData& data : shader->GetScalaPropertyDatas())
  {
    // プロパティの登録
    MaterialPropertyData pdata = MaterialPropertyData();
    pdata.type_ = static_cast<T_FIXED_UINT8>(GetMaterialPropertyType(static_cast<VariableType>(data.variable_type_)));
    pdata.count_ = 1;
    pdata.offset_ = data_offset;
    dest->property_table_[data.name_] = pdata;
    // データの初期化
    VariableType type = static_cast<VariableType>(data.variable_type_);
    (*(T_FLOAT*)&dest->data_[data_offset]) = data.init_value_;
    data_offset += Shader::GetVariableTypeSize(type);
  }
  for (const VectorPropertyData& data : shader->GetVectorPropertyDatas())
  {
    // プロパティの登録
    MaterialPropertyData pdata = MaterialPropertyData();
    pdata.type_ = static_cast<T_FIXED_UINT8>(GetMaterialPropertyType(static_cast<VariableType>(data.variable_type_)));
    pdata.count_ = 4;
    pdata.offset_ = data_offset;
    dest->property_table_[data.name_] = pdata;
    // データの初期化
    VariableType type = static_cast<VariableType>(data.variable_type_);
    ((T_FLOAT*)&dest->data_[data_offset])[0] = data.init_value0_;
    ((T_FLOAT*)&dest->data_[data_offset])[1] = data.init_value1_;
    ((T_FLOAT*)&dest->data_[data_offset])[2] = data.init_value2_;
    ((T_FLOAT*)&dest->data_[data_offset])[3] = data.init_value3_;
    data_offset += Shader::GetVariableTypeSize(type) * 4;
  }
  for (const ColorPropertyData& data : shader->GetColorPropertyDatas())
  {
    // プロパティの登録
    MaterialPropertyData pdata = MaterialPropertyData();
    pdata.type_ = static_cast<T_FIXED_UINT8>(MaterialPropertyType::kColor);
    pdata.count_ = 1;
    pdata.offset_ = data_offset;
    dest->property_table_[data.name_] = pdata;
    // データの初期化
    ((T_FLOAT*)&dest->data_[data_offset])[0] = data.init_r_;
    ((T_FLOAT*)&dest->data_[data_offset])[1] = data.init_g_;
    ((T_FLOAT*)&dest->data_[data_offset])[2] = data.init_b_;
    ((T_FLOAT*)&dest->data_[data_offset])[3] = data.init_a_;
    data_offset += Shader::GetVariableTypeSize(VariableType::kColor);
  }
  T_UINT32 texture_offset = 0;
  dest->textures_.resize(shader->GetSamplerPropertyDatas().size());
  for (const SamplerPropertyData& data : shader->GetSamplerPropertyDatas())
  {
    // プロパティの登録
    MaterialPropertyData pdata = MaterialPropertyData();
    pdata.type_ = static_cast<T_FIXED_UINT8>(MaterialPropertyType::kTexture);
    pdata.count_ = 1;
    pdata.offset_ = texture_offset;
    dest->property_table_[data.name_] = pdata;
    // データの初期化
    if (data.default_texture_ == static_cast<T_UINT8>(DefaultTextureType::kWhite))
    {
      dest->textures_[texture_offset] = DefaultUniqueID::TEXTURE_WHITE;
    }
    texture_offset += 1;
  }
}

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcMaterial, const MaterialData& data)
{
  this->property_table_ = data.property_table_;
  this->data_ = data.data_;
  const T_UINT32 texture_count = (T_UINT32)data.textures_.size();
  this->textures_.resize(texture_count);
  for (T_UINT32 i = 0; i < texture_count; ++i)
  {
    this->textures_[i] = AssetManager::Load<rcTexture>(data.textures_[i]);
  }

  this->constant_buffer_ = rcConstantBuffer::Create(
    Shader::ConstantBufferId::kProperty,
    (T_UINT32)this->data_.size()
  );

  this->shader_ = 
    data.shader_unique_id_ != 0 ?
    AssetManager::Load<rcShader>(data.shader_unique_id_) :
    AssetManager::Load<rcShader>(DefaultUniqueID::SHADER_NO_SHADING)
  ;

  this->SetMainTexture(
    data.main_texture_unique_id_ != 0 ?
    AssetManager::Load<rcTexture>(data.main_texture_unique_id_) :
    AssetManager::Load<rcTexture>(DefaultUniqueID::TEXTURE_WHITE)
  );

  return true;
}

GG_INIT_FUNC_IMPL_1(rcMaterial, const SharedRef<rcShader>& shader)
{
  MaterialData data = MaterialData();
  MaterialData::CreateWithShader(shader, &data);
  return rcMaterial::Init(data);
}

GG_INIT_FUNC_IMPL_1(rcMaterial, const rcMaterial& o)
{
  this->shader_ = o.shader_;
  this->property_table_ = o.property_table_;
  this->data_ = o.data_;
  this->textures_ = o.textures_;
  this->main_texture_ = o.main_texture_;

  this->constant_buffer_ = rcConstantBuffer::Create(
    Shader::ConstantBufferId::kProperty,
    (T_UINT32)this->data_.size()
  );
  this->constant_buffer_->CommitChanges(this->data_.data());

  return true;
}

// =================================================================
// Methods
// =================================================================
UniqueRef<rcMaterial> rcMaterial::Clone() const
{
  return rcMaterial::Create(*this);
}

UniqueRef<rcMaterial> rcMaterial::InitialClone() const
{
  return rcMaterial::Create(this->shader_);
}

void rcMaterial::CommitChanges()
{
  this->constant_buffer_->CommitChanges(this->data_.data());
}

void rcMaterial::SetBuffer() const
{
  this->constant_buffer_->SetBuffer();
  const T_UINT32 texture_count = (T_UINT32)this->textures_.size();

  this->main_texture_->SetToHardware(0);
  for (T_UINT32 i = 0; i < texture_count; ++i)
  {
    this->textures_[i]->SetToHardware(i + 1);
  }
}
