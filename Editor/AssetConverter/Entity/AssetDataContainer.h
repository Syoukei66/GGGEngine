#pragma once

class AssetConverter;

/*!
 * @brief AssetDataContainerで必要なテンプレート引数が
 * 無くても扱えるようにするためのインターフェース
 */
class IAssetDataContainer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~IAssetDataContainer() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void SaveCache(const URI& uri) = 0;

};

/*!
 * @brief AssetEntityが管理する変換後Assetのキャッシュデータの容器
 * 型のチェックやデストラクタの起動などを行えるようになっている
 */
template <class AssetData_>
class AssetDataContainer : public IAssetDataContainer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief コンストラクタ
   * @param data データ
   */
  AssetDataContainer(AssetData_* data)
    : data_(data)
  {
  }

  virtual ~AssetDataContainer()
  {
    delete this->data_;
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void SaveCache(const URI& uri) override
  {
    // キャッシュデータが無いタイプのアセットもある
    // (RawAssetをコピーするだけのものなど)
    if (!this->data_)
    {
      return;
    }
    const std::string& path = FileUtil::CreateCachePath(uri);
    FileUtil::PrepareDirectory(path);
    CerealIO::Binary::Export<AssetData_>(path.c_str(), this->GetData());
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
