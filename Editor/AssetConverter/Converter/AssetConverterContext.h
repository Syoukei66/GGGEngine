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
  AssetConverterContext(UniqueIdTable* unique_id_table);
  virtual ~AssetConverterContext();

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
   * @brief 条件を満たすAssetEntityを全て取得する
   * @param dest 受取先
   * @param cond 条件
   */
  void GetEntities(std::vector<SharedRef<AssetEntity>>* dest, const std::function<bool(const SharedRef<AssetEntity>&)>& cond);

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
  /*!
   * @brief デフォルトアセットIDからデフォルトアセットのURIを取得する
   * @param default_uid デフォルトアセットID
   * @return デフォルトアセットのURI
   */
  inline const URI& GetDefaultAssetURI(T_UINT32 default_uid)
  {
    return this->default_asset_uri_[default_uid];
  }

  /*!
   * @brief AssetConverterを追加する
   * @param converter 追加するAssetConverter
   * @return 追加したAssetConverter
   */
  AssetConverter* AddConverter(AssetConverter* converter);

  /*!
   * @brief DefaultAsset用のAssetConverterを追加する
   * @param converter 追加するAssetConverter
   * @return 追加したAssetConverter
   */
  AssetConverter* AddDefaultAssetConverter(AssetConverter* converter);

  /*!
   * @brief AssetCovnerterIdからAssetConverterを取得する
   * @param id ID
   * @return 指定したIDを持つAssetConverter
   */
  AssetConverter* GetConverter(const std::string& id);

  /*!
   * @brief AssetConverterIdからconst AssetConverterを取得する
   * @param id ID
   * @return 指定したIDを持つAssetConverter
   */
  const AssetConverter* GetConverter(const std::string& id) const;

  // =================================================================
  // Data Members
  // =================================================================
protected:
  UniqueIdTable* unique_id_table_;
  std::unordered_map<std::string, AssetConverter*> converter_map_;
  std::unordered_map<std::string, AssetConverter*> default_asset_converter_map_;
  std::unordered_map<T_UINT32, URI> default_asset_uri_;
  std::unordered_map<std::string, T_UINT32> default_asset_unique_id_;
  std::unordered_map<T_UINT32, SharedRef<AssetEntity>> asset_entities_;

};
