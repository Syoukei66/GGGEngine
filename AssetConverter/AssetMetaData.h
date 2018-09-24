#pragma once
#include <string>
#include <unordered_set>
#include "../Core/NativeType.h"

#include "Cereal/cereal.hpp"
#include "Cereal/archives/json.hpp"
#include "Cereal/types/string.hpp"
#include "Cereal/types/unordered_set.hpp"
#include "Cereal/types/utility.hpp"

class AssetConverterContext;

class AssetMetaData
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static AssetMetaData* Create(const std::string& asset_path, AssetConverterContext* context);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetMetaData(const std::string& asset_path, AssetConverterContext* context);
  AssetMetaData();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Save();

  AssetMetaData* CreateChild(const std::string& child_path, AssetConverterContext* context);

  void ResetTimeStamp();
  bool UpdateTimeStamp();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline T_UINT32 GetUniqueId() const
  {
    return this->unique_id_;
  }

  // =================================================================
  // Serialize Method
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(CEREAL_NVP(path_));
    ar(CEREAL_NVP(unique_id_));
    ar(CEREAL_NVP(source_));
    ar(CEREAL_NVP(related_unique_ids_));
    ar(CEREAL_NVP(time_stamp_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string path_;
  T_UINT32 unique_id_;
  T_UINT32 source_;
  std::unordered_set<T_UINT32> related_unique_ids_;

  std::string time_stamp_;

};
