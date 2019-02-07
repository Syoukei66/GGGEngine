#pragma once

#include <Core/Application/Platform/API/_Resource/ConstantBuffer.h>
#include <Asset/Texture/Texture.h>
#include <Asset/Shader/Shader.h>

/*!
 * @brief マテリアルのプロパティ情報
 * プロパティのタイプやデータのバイトオフセットなどが格納される
 */
struct MaterialPropertyData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(MaterialPropertyData)
  {
    archive(type_);
    archive(count_);
    archive(offset_);
  }

  // =================================================================
  // Data Member
  // =================================================================
public:
  T_FIXED_UINT8 type_; // MaterialPropertyType
  T_FIXED_UINT8 count_;
  T_FIXED_UINT32 offset_;
};

/*!
 * @brief マテリアルのデータ
 * シリアライズされてアセットとして扱われる
 */
struct MaterialData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(MaterialData)
  {
    archive(shader_unique_id_);

    archive(main_texture_unique_id_);

    archive(property_table_);
    archive(data_);
    archive(textures_);
  }
  // =================================================================
  // CreateFunction
  // =================================================================
  static void CreateWithShader(const SharedRef<rcShader>& shader, MaterialData* dest);

  // =================================================================
  // Data Member
  // =================================================================
public:
  T_FIXED_UINT32 shader_unique_id_;

  T_FIXED_UINT32 main_texture_unique_id_;

  std::unordered_map<std::string, MaterialPropertyData> property_table_;
  std::vector<unsigned char> data_;
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
    this->main_texture_ = texture;
  }
  GG_INLINE SharedRef<const rcTexture> GetMainTexture() const
  {
    return this->main_texture_;
  }

  GG_INLINE T_UINT32 GetDataHandle(const std::string& property_name, T_UINT8 index) const
  {
    return this->property_table_.at(property_name).offset_ +
      index * (T_UINT32)Shader::GetMaterialPropertySize(static_cast<Shader::MaterialPropertyType>(this->property_table_.at(property_name).type_));
  }
  GG_INLINE T_UINT32 GetTextureHandle(const std::string& property_name) const
  {
    return this->property_table_.at(property_name).offset_;
  }

  // プロパティの取得
  template <class Type_>
  GG_INLINE Type_& GetProperty(const std::string& property_name, T_UINT8 index = 0)
  {
    return this->GetProperty<Type_>(this->GetDataHandle(property_name, index));
  }
  template <class Type_>
  GG_INLINE Type_& GetProperty(T_UINT32 handle)
  {
    return (*(Type_*)&this->data_[handle]);
  }
  template <class Type_>
  GG_INLINE const Type_& GetProperty(const std::string& property_name, T_UINT8 index = 0) const
  {
    return this->GetProperty<Type_>(this->GetDataHandle(property_name, index));
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

  SharedRef<const rcTexture> main_texture_;

  // シェーダープロパティ
  std::unordered_map<std::string, MaterialPropertyData> property_table_;
  std::vector<unsigned char> data_;
  std::vector<SharedRef<const rcTexture>> textures_;

  SharedRef<rcConstantBuffer> constant_buffer_;

};
