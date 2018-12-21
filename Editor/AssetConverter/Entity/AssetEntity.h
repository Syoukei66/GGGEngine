#pragma once

#include <set>
#include <URI.h>

class AssetMetaData;

#define ENTITY_ID(id) public:\
enum { ID = id };\
virtual T_UINT32 GetID() const override\
{\
  return ID;\
}

class AssetEntity : public GGObject
{
public:
  // 依存関係を正しく解決できる順番で並べる
  enum EntityID
  {
    ID_TEXTURE,
    ID_CSV,
    ID_JSON,
    ID_SHADER,
    ID_SOUND,
    ID_DEFAULT_MESH,
    ID_DEFAULT_MATERIAL,
    ID_MODEL_MATERIAL,
    ID_STATIC_MODEL,
    ID_CHARACTER_MODEL,
  };

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_INIT_FUNC_1(AssetEntity, AssetMetaData*);
  GG_DESTRUCT_FUNC(AssetEntity);

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief 自身が管理しているデータに変更があった場合
   * AssetManager側へアセットの再登録を行う
   */
  void CommitChanges();

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

  /*!
   * @brief 参照しているアセットを追加する
   */
  void AddSubEntity(const SharedRef<AssetEntity>& entity);

protected:
  /*!
   * @brief 自分が管理しているリソースをAssetManagerへ上書き登録する
   */
  virtual void RegisterAssetManager(T_UINT32 uid, const std::string& extension) const = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual T_UINT32 GetID() const = 0;

  inline AssetMetaData* GetMetaData() const
  {
    return this->meta_data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetMetaData* meta_data_;
  std::vector<SharedRef<AssetEntity>> sub_entities_;
  bool is_dirty_;

};