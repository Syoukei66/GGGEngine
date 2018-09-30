#pragma once

#include <string>
#include <unordered_map>

#include <Cereal/cereal.hpp>
#include <Cereal/archives/json.hpp>
#include <Cereal/types/string.hpp>
#include <Cereal/types/unordered_map.hpp>
#include <Cereal/types/utility.hpp>
#include <Core/NativeType.h>

namespace DefaultUniqueID
{

enum 
{
  DEFAULT_UNIQUE_ID_BEGIN = 1000000,
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

  MESH_CUBE,
  MESH_PLANE,
  MESH_SPRITE,

  MATERIAL_WHITE,
  MATERIAL_SPRITE,
};

}

class UniqueIdTable
{
public:

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

  inline void RegisterDefaultAssetUniqueID(T_UINT32 default_id, T_UINT32 uid)
  {
    this->default_asset_unique_id_table_[default_id] = uid;
  }

  inline T_UINT32 GetDefaultAssetUniqueID(T_UINT32 default_id) const
  {
    return this->default_asset_unique_id_table_.at(default_id);
  }

  // =================================================================
  // Serialize Method
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("Table", this->table_));
    ar(cereal::make_nvp("DefaultAssetUniqueID", this->default_asset_unique_id_table_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<std::string, T_UINT32> table_;
  std::unordered_map<T_UINT32, T_UINT32> default_asset_unique_id_table_;

};
CEREAL_CLASS_VERSION(UniqueIdTable, 1);
