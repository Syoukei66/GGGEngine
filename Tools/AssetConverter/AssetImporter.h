#pragma once

#include <string>
#include <unordered_map>
#include <Core/NativeType.h>
#include "URI.h"

class AssetInfo;
class AssetConverterContext;

template <class Entity_>
class AssetImporter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetImporter(const std::vector<std::string>& extensions);
  virtual ~AssetImporter();

  // =================================================================
  // Methods
  // =================================================================
public:
  GG_INLINE bool IsTarget(const URI& uri);
  GG_INLINE bool Reserve(const URI& uri, AssetConverterContext* context);

  void Import(std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context);
  //アセットが参照しているアセットのロードが行われる為、
  //一括ループではなく１つずつロードした方が安全
  bool ImportOnce(std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context);
  bool ImportOnce(T_UINT32 unique_id, std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context);
  Entity_* ImportImmediately(const URI& uri, std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context);

protected:
  virtual Entity_* ImportProcess(AssetInfo* info, AssetConverterContext* context) = 0;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::vector<std::string> target_extensions_;
  std::unordered_map<T_UINT32, AssetInfo*> reserve_assets_;

};

#include "AssetInfo.h"

// =================================================================
// Constructor / Destructor
// =================================================================
template<class Entity_>
GG_INLINE AssetImporter<Entity_>::AssetImporter(const std::vector<std::string>& extensions)
  : target_extensions_(extensions)
{
}

template<class Entity_>
GG_INLINE AssetImporter<Entity_>::~AssetImporter() {}

// =================================================================
// Methods
// =================================================================
template<class Entity_>
GG_INLINE bool AssetImporter<Entity_>::IsTarget(const URI& uri)
{
  return std::find(this->target_extensions_.begin(), this->target_extensions_.end(), uri.GetExtension()) != this->target_extensions_.end();
}

template<class Entity_>
GG_INLINE bool AssetImporter<Entity_>::Reserve(const URI& uri, AssetConverterContext* context)
{
  //対応する拡張子かチェック
  if (!this->IsTarget(uri))
  {
    return false;
  }
  AssetInfo* info = AssetInfo::Create(uri, context);
  this->reserve_assets_[info->GetUniqueID()] = info;
  return true;
}

template<class Entity_>
GG_INLINE void AssetImporter<Entity_>::Import(std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context)
{
  for (auto& pair : this->reserve_assets_)
  {
    (*dest)[pair.first] = this->ImportProcess(pair.second, context);
  }
  this->reserve_assets_.clear();
}

//アセットが参照しているアセットのロードが行われる為、
//一括ループではなく１つずつロードした方が安全
template<class Entity_>
GG_INLINE bool AssetImporter<Entity_>::ImportOnce(std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context)
{
  const auto& begin = this->reserve_assets_.begin();
  if (begin == this->reserve_assets_.end())
  {
    return false;
  }
  T_UINT32 unique_id = begin->first;
  AssetInfo* info = begin->second;
  this->reserve_assets_.erase(begin->first);
  //イテレーター処理が終わった後にImport処理を行う事で
  //割り込みが発生しても安全に処理できる
  (*dest)[unique_id] = this->ImportProcess(info, context);
  return true;
}

template<class Entity_>
GG_INLINE bool AssetImporter<Entity_>::ImportOnce(T_UINT32 unique_id, std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context)
{
  const auto& itr = this->reserve_assets_.find(unique_id);
  if (itr == this->reserve_assets_.end())
  {
    return false;
  }
  AssetInfo* info = itr->second;
  this->reserve_assets_.erase(itr->first);
  //イテレーター処理が終わった後にImport処理を行う事で
  //割り込みが発生しても安全に処理できる
  (*dest)[unique_id] = this->ImportProcess(info, context);
  return true;
}

template<class Entity_>
GG_INLINE Entity_* AssetImporter<Entity_>::ImportImmediately(const URI& uri, std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context)
{
  AssetInfo* info = nullptr;

  //既に予約済みかどうかチェックする
  T_UINT32 uid = context->GetUniqueID(uri);
  const auto& itr = this->reserve_assets_.find(uid);
  if (itr != this->reserve_assets_.end())
  {
    info = itr->second;
    //予約を解除しとく
    this->reserve_assets_.erase(itr);
  }
  //予約済みじゃなかったらAssetInfoを作るところから
  else
  {
    //対応する拡張子かチェック
    if (!IsTarget(uri))
    {
      return nullptr;
    }
    info = AssetInfo::Create(uri, context);
  }
  Entity_* ret = this->ImportProcess(info, context);
  (*dest)[info->GetUniqueID()] = ret;
  return ret;
}

