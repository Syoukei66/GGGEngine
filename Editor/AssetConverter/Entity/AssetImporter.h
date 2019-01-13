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

  // =================================================================
  // Methods
  // =================================================================
public:
  bool IsTarget(const URI& uri);

  void* ImportImmediately(AssetMetaData* meta_data, AssetConverterContext* context);

protected:
  /*!
   * @brief アセットのインポート実処理
   * 派生クラス側で実際のインポート処理を記述する。
   */
  virtual void* ImportProcess(AssetMetaData* meta, AssetConverterContext* context) = 0;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::vector<std::string> target_extensions_;

};
