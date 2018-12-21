#include "Material.h"

#include <Asset/Shader/Shader.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcMaterial, const MaterialData& data)
{
  this->data_offset_table_ = data.data_offset_table_;
  this->data_ = data.data_;

  this->texture_index_table_ = data.texture_index_table_;
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
  this->shader_ = shader;

  using namespace Shader;

  T_UINT32 data_offset = 0;
  for (const ScalaPropertyData& data : shader->GetScalaPropertyDatas())
  {
    this->data_offset_table_[data.name_] = data_offset;
    VariableType type = static_cast<VariableType>(data.variable_type_);
    (*(T_FLOAT*)&this->data_[data_offset]) = data.init_value_;
    data_offset += sizeof(T_FLOAT);
  }
  for (const VectorPropertyData& data : shader->GetVectorPropertyDatas())
  {
    this->data_offset_table_[data.name_] = data_offset;
    VariableType type = static_cast<VariableType>(data.variable_type_);
    ((T_FLOAT*)&this->data_[data_offset])[0] = data.init_value0_;
    ((T_FLOAT*)&this->data_[data_offset])[1] = data.init_value1_;
    ((T_FLOAT*)&this->data_[data_offset])[2] = data.init_value2_;
    ((T_FLOAT*)&this->data_[data_offset])[3] = data.init_value3_;
    data_offset += sizeof(T_FLOAT) * 4;
  }
  for (const ColorPropertyData& data : shader->GetColorPropertyDatas())
  {
    this->data_offset_table_[data.name_] = data_offset;
    ((T_FLOAT*)&this->data_[data_offset])[0] = data.init_r_;
    ((T_FLOAT*)&this->data_[data_offset])[1] = data.init_g_;
    ((T_FLOAT*)&this->data_[data_offset])[2] = data.init_b_;
    ((T_FLOAT*)&this->data_[data_offset])[3] = data.init_a_;
    data_offset += sizeof(T_FLOAT) * 4;
  }
  //TODO: SamplerProperty‚à’Ç‰Á‚·‚é
  T_UINT32 texture_offset = 0;
  for (const SamplerPropertyData& data : shader->GetSamplerPropertyDatas())
  {
    if (data.default_texture_ == static_cast<T_UINT8>(DefaultTextureType::kWhite))
    {
      this->textures_[texture_offset] = AssetManager::Load<rcTexture>(DefaultUniqueID::TEXTURE_WHITE);
    }
    this->texture_index_table_[data.name_] = texture_offset;
    texture_offset += 1;
  }

  this->constant_buffer_ = rcConstantBuffer::Create(
    Shader::ConstantBufferId::kProperty,
    (T_UINT32)this->data_.size()
  );
  this->constant_buffer_->CommitChanges(this->data_.data());

  this->SetMainTexture(AssetManager::Load<rcTexture>(DefaultUniqueID::TEXTURE_WHITE));

  return true;
}

GG_INIT_FUNC_IMPL_1(rcMaterial, const rcMaterial& o)
{
  this->shader_ = o.shader_;
  this->data_offset_table_ = o.data_offset_table_;
  this->data_ = o.data_;
  this->texture_index_table_ = o.texture_index_table_;
  this->textures_ = o.textures_;

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

  this->main_texture_->GetNativeResource()->SetResource(0);
  for (T_UINT32 i = 0; i < texture_count; ++i)
  {
    this->textures_[i]->GetNativeResource()->SetResource(i + 1);
  }
}
