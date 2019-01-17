#pragma once

/*!
 * @brief AssetDataCacheで必要なテンプレート引数が
 * 無くても扱えるようにするためのインターフェース
 */
class IAssetDataCache
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~IAssetDataCache() = default;
};

/*!
 * @brief AssetEntityが管理する変換後Assetのキャッシュデータの容器
 * 型のチェックやデストラクタの起動などを行えるようになっている
 */
template <typename AssetData_>
class AssetDataCache : public IAssetDataCache
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetDataCache(AssetData_* data)
    : data_(data)
  {}

  virtual ~AssetDataCache()
  {
    delete this->data_;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  AssetData_* GetData()
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetData_* data_;

};
