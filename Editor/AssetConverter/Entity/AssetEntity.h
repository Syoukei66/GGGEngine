#pragma once

#include <set>
#include <URI.h>
#include "AssetDataCache.h"

class AssetConverterContext;
class AssetConverter;
class AssetMetaData;

/*!
 * @brief AssetConverterで扱うAssetの実体
 */
class AssetEntity : public GGObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(AssetEntity);
  GG_CREATE_FUNC_1(AssetEntity, AssetMetaData*);
  GG_CREATE_FUNC_2(AssetEntity, AssetMetaData*, IAssetDataCache*);
  GG_DESTRUCT_FUNC(AssetEntity);

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * 自身が参照しているアセット含めて全てのアセットをロードする。
   * 既にロード済みなら何も行わない。
   * @param context
   * @return ロードが行われたならtrue
   */
  bool Load(AssetConverterContext* context);

  /*!
   * 対象のアセットを変換し、変換後のデータを
   * ランタイム用のディレクトリにランタイム用のフォーマットで出力する。
   * @param context
   */
  void Export(AssetConverterContext* context);

private:
  /*!
   * 対象のアセットをインポート。
   * 同時にアセットの依存関係を作成し、
   * 自身が参照しているアセットのロードも行う。
   * @param context
   */
  void Import(AssetConverterContext* context);

  /*!
   * @brief 自身が管理しているデータに変更があった場合
   * AssetManager側へアセットの再登録を行う
   */
  void CommitChanges(AssetConverterContext* context);

  /*!
   * @brief 自身が参照しているアセットに変更があるか調べ、
   * 変更があった場合タイムスタンプを更新し、update_entitiesに追加し、ダーティフラグを立てる
   */
  void CheckAssetChanged(AssetConverterContext* context, std::set<SharedRef<AssetEntity>>* update_entities);

  /*!
   * @brief 自身が参照しているサブアセットに変更があるか調べ、
   * 変更があった場合ダーティフラグを立てる
   * MEMO: 本来はCheckAssetChangedで行っていた処理だったが、
   * タイムスタンプの監視と同時にサブアセットの走査を行うと、
   * 複数回参照されてるアセットがあった場合に
   * チェックのタイミングのズレによる不整合が発生する事がある為、処理を分割した
   */
  bool CheckSubAssetChanged(AssetConverterContext* context);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const AssetMetaData* GetMetaData() const
  {
    return this->meta_data_;
  }
  inline AssetMetaData* GetMetaData()
  {
    return this->meta_data_;
  }

  void SetData(IAssetDataCache* data);

  inline const IAssetDataCache* GetData() const
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetMetaData* meta_data_;
  AssetConverter* converter_;
  IAssetDataCache* data_;
  bool is_dirty_;

};