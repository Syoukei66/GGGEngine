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
};

/*!
 * @brief AssetEntityが管理する変換後Assetのキャッシュデータの容器
 * 型のチェックやデストラクタの起動などを行えるようになっている
 */
template <typename AssetData_>
class AssetDataContainer : public IAssetDataContainer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief コンストラクタ
   * @param data データ
   * @param converter データを作成したConverter
   */
  AssetDataContainer(AssetData_* data, const AssetConverter* converter)
    : data_(data)
    , converter_(converter)
  {
  }

  virtual ~AssetDataContainer()
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

  const AssetConverter* GetConverter()
  {
    return this->converter_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetData_* data_;
  const AssetConverter* converter_;

};
