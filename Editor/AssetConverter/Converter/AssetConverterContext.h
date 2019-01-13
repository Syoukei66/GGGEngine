#pragma once

#include "URI.h"
#include "AssetConverterManager.h"

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
   * @brief Assetフォルダを探索し、未登録のファイルを見つけAssetEntityを作成する。
   */
  void Fetch();

  /*!
   * @brief 全てのAssetEntityに対して処理を行う
   * @param func AssetEntityに対して行う処理
   */
  void VisitAllEntity(const std::function<void(const SharedRef<AssetEntity>&)>& func);

  /*!
   * @brief AssetEntityを追加する
   * @param entity AssetEntity
   * @return 追加したAssetEntity
   */
  SharedRef<AssetEntity> AddEntity(const SharedRef<AssetEntity>& entity);

  /*!
   * @brief URIからAssetEntityを取得する
   * @param uri URI
   * @return 取得したAssetEntity。登録されていない場合はnullptrが帰ってくる。
   */
  SharedRef<AssetEntity> GetEntity(const URI& uri);

  /*!
   * @brief UniqueIdからAssetEntityを取得する
   * @param unique_id UniqueId
   * @return 取得したAssetEntity。登録されていない場合はエラーが発生する。
   */
  SharedRef<AssetEntity> GetEntity(T_UINT32 unique_id);

  /*!
   * @brief URIからUniqueIdを発行する。URIはランタイム時のURIに変換される。
   * 既に発行済みのURIが来た場合は発行済みの値を返す。
   * @param uri エディタでのURI
   * @return URIから発行したUniqueId
   */
  T_UINT32 PublishUniqueID(const URI& uri);

  /*!
   * @brief URIからUniqueIdを取得する。URIはランタイム時のURIに変換される。
   * 発行されてないURIが来た場合はエラー
   * @param uri エディタでのURI
   * @return URIから取得したUniqueId
   */
  T_UINT32 GetUniqueID(const URI& uri) const;

  /*!
   * @brief URIを指定してデフォルトアセットのUniqueIdを登録する
   * @param default_uid デフォルトアセットのUniqueId
   * @param uri デフォルトアセットのURI
   */
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
