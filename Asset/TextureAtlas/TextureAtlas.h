#pragma once

#include <Core/Application/Platform/API/_Asset/Texture/Texture.h>
#include <Asset/Mesh/Mesh.h>

struct TextureAtlasData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(TextureAtlasData)
  {
    archive(texture_unique_id_);
    archive(mesh_unique_id_);
  }

  // =================================================================
  // Data Member
  // =================================================================
public:
  T_FIXED_UINT32 texture_unique_id_;
  T_FIXED_UINT32 mesh_unique_id_;
};

/*!
 * @brief １つのテクスチャとそのテクスチャを使用するメッシュの集合
 * Spriteのドローコールを抑える為に、AssetConverterによって作成される。
 */
class rcTextureAtlas : public GGAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcTextureAtlas);
  GG_ASSET(rcTextureAtlas, TextureAtlasData);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<const rcTexture> GetTexture() const
  {
    return this->texture_;
  }

  GG_INLINE SharedRef<const rcMesh> GetMesh() const
  {
    return this->mesh_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  SharedRef<const rcTexture> texture_;
  SharedRef<const rcMesh> mesh_;

};
