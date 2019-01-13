#pragma once

#include "URI.h"

/*!
 * Importer‚ÌÝ’èB
 */
class ImporterSetting
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ImporterSetting()
    : converter_id_()
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

  inline const URI& GetMidFileURI() const
  {
    return this->mid_file_uri_;
  }

  inline bool IsMidFileDirty() const
  {
    return this->mid_file_dirty_;
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

  URI mid_file_uri_;
  bool mid_file_dirty_;

  std::unordered_set<T_UINT32> sub_asset_unique_ids_;

};