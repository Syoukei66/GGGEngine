#pragma once

#include "URI.h"

struct Setting;

class AssetConverter;
class AssetConverterManager;
class AssetMetaData;
class UniqueIdTable;
class AssetEntity;

class AssetConverterContext
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverterContext(UniqueIdTable* unique_id_table, AssetConverterManager* converter_manager);
  virtual ~AssetConverterContext() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief Assetフォルダを探索し、未登録のファイルを見つけAssetEntityを作成したり、
   */
  void Fetch();

  void VisitAllEntity(const std::function<void(const SharedRef<AssetEntity>&)>& func);

  SharedRef<AssetEntity> AddEntity(const SharedRef<AssetEntity>& entity);

  SharedRef<AssetEntity> GetEntity(const URI& uri);
  SharedRef<AssetEntity> GetEntity(T_UINT32 unique_id);

  T_UINT32 PublishUniqueID(const URI& uri);
  T_UINT32 GetUniqueID(const URI& uri) const;
  void RegisterDefaultUniqueID(T_UINT32 default_uid, const URI& uri);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const URI& GetDefaultAssetURI(T_UINT32 default_uid)
  {
    return this->default_asset_uri_[default_uid];
  }
  inline AssetConverter* GetConverter(const std::string& converter_id)
  {
    return this->converter_manager_->GetConverter(converter_id);
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  UniqueIdTable* unique_id_table_;
  AssetConverterManager* converter_manager_;
  std::unordered_map<T_UINT32, URI> default_asset_uri_;
  std::unordered_map<T_UINT32, SharedRef<AssetEntity>> asset_entities_;

};
