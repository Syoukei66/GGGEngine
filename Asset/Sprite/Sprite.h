#pragma once

class rcTexture;
class rcMesh;

struct SpriteData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(SpriteData)
  {
    archive(texture_atlas_unique_id_);
    archive(submesh_index_);
  }

  // =================================================================
  // Data Member
  // =================================================================
public:
  T_FIXED_UINT32 texture_atlas_unique_id_;
  T_FIXED_UINT32 submesh_index_;
};

/*!
* @brief スプライト
* １つのテクスチャと１つのメッシュのセットとなっている
*/
class rcSprite : public GGAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_ASSET(rcSprite, SpriteData);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<const rcMesh> GetMesh() const
  {
    return this->mesh_;
  }

  GG_INLINE SharedRef<const rcTexture> GetTexture() const
  {
    return this->texture_;
  }

  GG_INLINE T_UINT32 GetSubmeshIndex() const
  {
    return this->submesh_index_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  SharedRef<const rcTexture> texture_;
  SharedRef<const rcMesh> mesh_;
  T_UINT32 submesh_index_;

};