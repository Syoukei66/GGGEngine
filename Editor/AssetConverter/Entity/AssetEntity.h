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
   * @brief 自身や参照しているアセット群に変更があるか調べ、
   * 変更があった場合アップデートする。
   */
  bool CheckChanged(std::set<SharedRef<AssetEntity>>* update_entities);

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