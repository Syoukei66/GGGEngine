#pragma once

#include <Core/Application/Platform/API/_Asset/Texture/Texture.h>
#include <Core/Application/Platform/API/_Resource/ConstantBuffer.h>
#include <Asset/Shader/Shader.h>

struct MaterialData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(MaterialData)
  {
    archive(shader_unique_id_);

    archive(data_offset_table_);
    archive(data_);

    archive(texture_index_table_);
    archive(textures_);
  }

  // =================================================================
  // Data Member
  // =================================================================
public:
  T_FIXED_UINT32 shader_unique_id_;

  std::unordered_map<std::string, T_UINT32> data_offset_table_;
  std::vector<unsigned char> data_;

  std::unordered_map<std::string, T_UINT32> texture_index_table_;
  std::vector<T_UINT32> textures_;
};

/*!
 * @brief マテリアル
 * シェーダーへのプロパティの受け渡しを担うクラス
 */
class rcMaterial : public GGAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcMaterial);
  GG_ASSET(rcMaterial, MaterialData);
  GG_CREATE_FUNC_1(rcMaterial, const SharedRef<rcShader>&);
  GG_CREATE_FUNC_1(rcMaterial, const rcMaterial&);

  // =================================================================
  // Methods
  // =================================================================
public:
  UniqueRef<rcMaterial> Clone() const;
  UniqueRef<rcMaterial> InitialClone() const;

  //TODO:MeshのようなToDataが欲しい

public:
  void CommitChanges();
  void SetBuffer() const;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE void SetShader(const SharedRef<rcShader>& shader)
  {
    this->shader_ = shader;
  }
  GG_INLINE SharedRef<rcShader> GetShader() const
  {
    return this->shader_;
  }

  GG_INLINE void SetMainTexture(const SharedRef<const rcTexture>& texture)
  {
    this->GetTexture("_MainTex") = texture;
  }
  GG_INLINE SharedRef<const rcTexture> GetMainTexture() const
  {
    return this->GetTexture("_MainTex");
  }

  GG_INLINE T_UINT32 GetDataHandle(const std::string& property_name) const
  {
    return this->data_offset_table_.at(property_name);
  }
  GG_INLINE T_UINT32 GetTextureHandle(const std::string& property_name) const
  {
    return this->texture_index_table_.at(property_name);
  }

  // プロパティの取得
  template <class Type_>
  GG_INLINE Type_& GetProperty(const std::string& property_name)
  {
    return this->GetProperty<Type_>(this->GetDataHandle(property_name));
  }
  template <class Type_>
  GG_INLINE Type_& GetProperty(T_UINT32 handle)
  {
    return (*(Type_*)&this->data_[handle]);
  }
  template <class Type_>
  GG_INLINE const Type_& GetProperty(const std::string& property_name) const
  {
    return this->GetProperty<Type_>(this->GetDataHandle(property_name));
  }
  template <class Type_>
  GG_INLINE const Type_& GetProperty(T_UINT32 handle) const
  {
    return (*(Type_*)&this->data_.at(handle));
  }

  // テクスチャプロパティの取得
  GG_INLINE SharedRef<const rcTexture>& GetTexture(const std::string& property_name)
  {
    return this->GetTexture(this->GetTextureHandle(property_name));
  }
  GG_INLINE SharedRef<const rcTexture>& GetTexture(T_UINT32 handle)
  {
    return this->textures_[handle];
  }
  GG_INLINE const SharedRef<const rcTexture>& GetTexture(const std::string& property_name) const
  {
    return this->GetTexture(this->GetTextureHandle(property_name));
  }
  GG_INLINE const SharedRef<const rcTexture>& GetTexture(T_UINT32 handle) const
  {
    return this->textures_.at(handle);
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  SharedRef<rcShader> shader_;

  // シェーダープロパティ
  std::unordered_map<std::string, T_UINT32> data_offset_table_;
  std::vector<unsigned char> data_;

  std::unordered_map<std::string, T_UINT32> texture_index_table_;
  std::vector<SharedRef<const rcTexture>> textures_;

  SharedRef<rcConstantBuffer> constant_buffer_;

};
