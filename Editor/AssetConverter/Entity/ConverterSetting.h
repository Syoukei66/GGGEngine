#pragma once

#include "URI.h"

/*!
 * Converter‚ÌÝ’èB
 */
class ConverterSetting
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ConverterSetting(const std::string& converter_id)
    : converter_id_(converter_id)
    , mid_file_uri_()
    , mid_file_dirty_(true)
    , sub_asset_unique_ids_()
  {}

  // =================================================================
  // Methods
  // =================================================================
public:
  inline void AddSubAsset(T_UINT32 uid)
  {
    this->sub_asset_unique_ids_.insert(uid);
  }

  inline void ClearSubAssets()
  {
    this->sub_asset_unique_ids_.clear();
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const std::string& GetConverterID() const
  {
    return this->converter_id_;
  }

  inline const std::unordered_set<T_UINT32>& GetSubAssetUniqueIds() const
  {
    return this->sub_asset_unique_ids_;
  }

  // =================================================================
  // Serialize Method
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(CEREAL_NVP(converter_id_));
    ar(CEREAL_NVP(mid_file_uri_));
    ar(CEREAL_NVP(mid_file_dirty_));
    ar(CEREAL_NVP(sub_asset_unique_ids_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string converter_id_;
  std::unordered_set<T_UINT32> sub_asset_unique_ids_;

};

CEREAL_CLASS_VERSION(ConverterSetting, 0);