#pragma once

class AssetInfo;

#define ENTITY_ID(id) public:\
enum { ID = id };\
virtual T_UINT32 GetID() const override\
{\
  return ID;\
}

class AssetEntity
{
public:
  enum EntityID
  {
    ID_DEFAULT_MESH,
    ID_DEFAULT_MATERIAL,
    ID_TEXTURE,
    ID_CSV,
    ID_JSON,
    ID_SHADER,
    ID_SOUND,
    ID_MODEL,
    ID_MODEL_MESH,
    ID_MODEL_MATERIAL,
  };

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetEntity(AssetInfo* info);
  virtual ~AssetEntity();

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief 自身が管理しているデータに変更があった場合
   * AssetManager側へアセットの再登録を行う
   */
  void CommitChanges();

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

  inline AssetInfo* GetAssetInfo() const
  {
    return this->info_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetInfo* info_;

};