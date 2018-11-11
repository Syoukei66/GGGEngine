#pragma once

namespace DefaultUniqueID
{

enum 
{
  DEFAULT_UID_BEGIN = 100000,
  SHADER_FLAT,
  SHADER_GOURAUD,
  SHADER_PHONG,
  SHADER_BLIN,
  SHADER_TOON,
  SHADER_OREN_NAYAR,
  SHADER_MINNAERT,
  SHADER_COOK_TORRANCE,
  SHADER_NO_SHADING,
  SHADER_FRESNEL,

  SHADER_SPRITE,

  SHADER_STENCIL_SHADOW,

  MESH_CUBE,
  MESH_PLANE,

  MATERIAL_WHITE,
  MATERIAL_LAMBERT,
  MATERIAL_SPRITE,
  MATERIAL_STENCIL_SHADOW,
};

}

class UniqueIdTable
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(UniqueIdTable)
  {
    archive(table_);
    archive(default_asset_unique_id_table_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  UniqueIdTable() = default;
  ~UniqueIdTable() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  T_UINT32 Publish(const std::string& path);
  T_UINT32 GetID(const std::string& path) const;

  GG_INLINE void RegisterDefaultAssetUniqueID(T_UINT32 default_id, T_UINT32 uid)
  {
    this->default_asset_unique_id_table_[default_id] = uid;
  }

  GG_INLINE void RegisterDefaultAssetUniqueID(T_UINT32 default_id, const std::string& path)
  {
    this->default_asset_unique_id_table_[default_id] = this->Publish(path);
  }

  GG_INLINE T_UINT32 GetDefaultAssetUniqueID(T_UINT32 default_id) const
  {
    return this->default_asset_unique_id_table_.at(default_id);
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<std::string, T_UINT32> table_;
  std::unordered_map<T_UINT32, T_UINT32> default_asset_unique_id_table_;

};
