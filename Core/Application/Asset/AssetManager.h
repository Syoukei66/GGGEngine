#pragma once

#include "AssetLoader.h"
#include "UniqueIdTable.h"

/*!
 * @brief AssetConverterで変換されたアセットを管理するクラス
 * UniqueIDを与えたロードや、ロードが複数回行われないようにキャッシュする機能などがある。
 */
class AssetManager
{
  GG_SINGLETON(AssetManager);

  friend class IAssetLoader;

  // =================================================================
  // Methods
  // =================================================================
public:
  static void Init();
  static void Init(UniqueIdTable* table);
  static void Uninit();
  static void UnloadCaches();

  /*!
   * @brief ユニークIDからアセットを取得する。
   * ユニークIDで登録されているアセットと型引数のアセットの型が違う場合の動作は未定義
   */
  template<class Asset_>
  static GG_INLINE SharedRef<Asset_> Load(T_UINT32 uid)
  {
    GG_ASSERT(uid != 0, "無効なアセットIDが入力されました");
    if (uid > DefaultUniqueID::DEFAULT_UID_BEGIN)
    {
      return ((AssetLoader<Asset_>*)Self().loaders_.at(Self().unique_id_table_->GetDefaultAssetUniqueID(uid)))->CreateFromFile();
    }
    return ((AssetLoader<Asset_>*)Self().loaders_.at(uid))->CreateFromFile();
  }

  /*!
  * @brief ファイルパスからアセットを取得する。
  * UniqueIDテーブルに登録されているパス以外のパスが指定されるとエラー
  * ユニークIDで登録されているアセットと型引数のアセットの型が違う場合の動作は未定義
  */
  template<class Asset_>
  static GG_INLINE SharedRef<Asset_> Load(const std::string& path)
  {
    const T_UINT32 uid = Self().unique_id_table_->GetID(path);
    GG_ASSERT(uid != 0, "無効なファイルパスが入力されました");
    return ((AssetLoader<Asset_>*)Self().loaders_.at(uid))->CreateFromFile();
  }

  /*!
  * @brief ファイルパスからAssetLoaderを取得する。
  * ユニークIDで登録されているアセットと型引数のアセットの型が違う場合の動作は未定義
  */
  template<class Asset_>
  static GG_INLINE const AssetLoader<Asset_>& GetLoader(T_UINT32 uid)
  {
    GG_ASSERT(uid != 0, "無効なアセットIDが入力されました");
    if (uid > DefaultUniqueID::DEFAULT_UID_BEGIN)
    {
      return (const AssetLoader<Asset_>&)*Self().loaders_.at(Self().unique_id_table_->GetDefaultAssetUniqueID(uid));
    }
    return (const AssetLoader<Asset_>&)*Self().loaders_.at(uid);
  }

  /*!
  * @brief ファイルパスからAssetLoaderを取得する。
  * UniqueIDテーブルに登録されているパス以外のパスが指定されるとエラー
  * ユニークIDで登録されているアセットと型引数のアセットの型が違う場合の動作は未定義
  */
  template<class Asset_>
  static GG_INLINE const AssetLoader<Asset_>& GetLoader(const std::string& path)
  {
    return (const AssetLoader<Asset_>&)*Self().loaders_.at(Self().unique_id_table_->GetID(path));
  }

  /*!
   * @brief AssetLoaderを登録する。
   * この処理はAssetConverterが自動生成したコードで行われる為、
   * ユーザー側が使用する事は無い。
   * ユーザー側が使用した際の動作は未定義
   */
  template<class Asset_>
  static GG_INLINE const AssetLoader<Asset_>& AddAsset(T_UINT32 uid, const std::string& extension)
  {
    Self().loaders_.emplace(uid, new AssetLoader<Asset_>(uid, std::to_string(uid) + "." + extension));
    return (const AssetLoader<Asset_>&)*Self().loaders_.at(uid);
  }
  
  /*!
   * @brief AssetLoaderを登録する。
   * メモリ上にあるデータをローダーに直接登録する
   * 既にアセットがあった場合はそのアセットを上書きする
   */
  template<class Asset_>
  static GG_INLINE const AssetLoader<Asset_>& AddAsset(T_UINT32 uid, const std::string& extension, const SharedRef<Asset_>& asset)
  {
    Self().loaders_[uid] = new AssetLoader<Asset_>(uid, std::to_string(uid) + "." + extension, asset);
    return (const AssetLoader<Asset_>&)*Self().loaders_.at(uid);
  }
  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<T_UINT32, IAssetLoader*> loaders_;
  UniqueIdTable* unique_id_table_;

};
