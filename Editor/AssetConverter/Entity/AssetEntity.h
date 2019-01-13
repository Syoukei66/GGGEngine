#pragma once

#include <set>
#include <URI.h>

class AssetConverterContext;
class AssetConverter;
class AssetMetaData;

class AssetEntity : public GGObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(AssetEntity);
  GG_CREATE_FUNC_1(AssetEntity, AssetMetaData*);
  GG_DESTRUCT_FUNC(AssetEntity);

  // =================================================================
  // Methods
  // =================================================================
public:
  void Import(AssetConverterContext* context);
  bool Reload(AssetConverterContext* context);
  void Export(AssetConverterContext* context);

private:
  /*!
   * @brief 自身が管理しているデータに変更があった場合
   * AssetManager側へアセットの再登録を行う
   */
  void CommitChanges(AssetConverterContext* context);

  /*!
   * @brief 自身が参照しているアセットに変更があるか調べ、
   * 変更があった場合タイムスタンプを更新し、update_entitiesに追加し、ダーティフラグを立てる
   */
  void CheckAssetChanged(std::set<SharedRef<AssetEntity>>* update_entities);

  /*!
   * @brief 自身が参照しているサブアセットに変更があるか調べ、
   * 変更があった場合ダーティフラグを立てる
   * MEMO: 本来はCheckAssetChangedで行っていた処理だったが、
   * タイムスタンプの監視と同時にサブアセットの走査を行うと、
   * 複数回参照されてるアセットがあった場合に
   * チェックのタイミングのズレによる不整合が発生する事がある為、処理を分割した
   */
  bool CheckSubAssetChanged();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const AssetMetaData* GetMetaData() const
  {
    return this->meta_data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetMetaData* meta_data_;
  bool is_dirty_;
  void* cache_;

};