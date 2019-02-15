#pragma once

namespace DefaultUniqueID
{

enum 
{
  DEFAULT_UID_BEGIN    = 100000,
  SHADER_ERRROR        = 100001,
  SHADER_FLAT          = 100002,
  SHADER_GOURAUD       = 100003,
  SHADER_PHONG         = 100004,
  SHADER_BLIN          = 100005,
  SHADER_TOON          = 100006,
  SHADER_OREN_NAYAR    = 100007,
  SHADER_MINNAERT      = 100008,
  SHADER_COOK_TORRANCE = 100009,
  SHADER_NO_SHADING    = 100010,
  SHADER_FRESNEL       = 100011,

  MESH_CUBE            = 100012,
  MESH_PLANE           = 100013,
  MESH_CAPSULE         = 100014,
  MESH_CUBE_SPHERE     = 100015,
  MESH_UV_SPHERE       = 100016,

  MATERIAL_WHITE       = 100017,
  MATERIAL_LAMBERT     = 100018,
  MATERIAL_UNLIT       = 100019,

  TEXTURE_WHITE        = 100020,
  TEXTURE_BLACK        = 100021,
  TEXTURE_GRAY         = 100022,
  TEXTURE_BUMP         = 100023,
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
  const std::string& GetPath(T_UINT32 uid) const;

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
  
  GG_INLINE const std::unordered_map<T_UINT32, T_UINT32>& GetDefaultAssetUniqueIdTable() const
  {
    return this->default_asset_unique_id_table_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<std::string, T_UINT32> table_;
  std::unordered_map<T_UINT32, T_UINT32> default_asset_unique_id_table_;

};
