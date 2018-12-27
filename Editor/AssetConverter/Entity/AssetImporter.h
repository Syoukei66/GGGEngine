#pragma once

#include "URI.h"

class AssetMetaData;
class AssetConverterContext;

class AssetImporter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetImporter(const std::vector<std::string>& extensions);
  virtual ~AssetImporter();

  // =================================================================
  // Methods
  // =================================================================
public:
  inline bool IsTarget(const URI& uri);
  inline bool Reserve(const URI& uri, T_UINT32 source_unique_id, AssetConverterContext* context);

  //アセットが参照しているアセットのロードが行われる為、
  //一括ループではなく１つずつロードした方が安全
  bool ImportOnce(std::unordered_map<T_UINT32, SharedRef<AssetEntity>>* dest, AssetConverterContext* context);
  bool ImportOnce(T_UINT32 unique_id, std::unordered_map<T_UINT32, SharedRef<AssetEntity>>* dest, AssetConverterContext* context);
  SharedRef<AssetEntity> ImportImmediately(const URI& uri, AssetConverterContext* context);

protected:
  /*!
   * @brief アセットのインポート実処理
   * 派生クラス側で実際のインポート処理を記述する。
   */
  virtual SharedRef<AssetEntity> ImportProcess(AssetMetaData* meta, AssetConverterContext* context) = 0;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::vector<std::string> target_extensions_;
  std::unordered_map<T_UINT32, AssetMetaData*> reserve_assets_;

};
