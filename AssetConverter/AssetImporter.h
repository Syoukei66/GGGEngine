#pragma once

#include "AssetInfo.h"

class AssetConverterContext;

template <class Entity_>
class AssetImporter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetImporter(const std::vector<std::string>& extensions)
    : target_extensions_(extensions)
  {
  }
  virtual ~AssetImporter() {}

  // =================================================================
  // Methods
  // =================================================================
public:
  inline bool ImportReserved() const
  {
    return this->reserve_assets_.size() > 0;
  }

  inline AssetInfo* Reserve(const std::string& directory_path, const std::string& file_name, const std::string& extension, AssetConverterContext* context)
  {
    //対応する拡張子かチェック
    if (std::find(this->target_extensions_.begin(), this->target_extensions_.end(), extension) == this->target_extensions_.end())
    {
      return nullptr;
    }
    AssetInfo* ret = AssetInfo::Create(directory_path, file_name, extension, context);
    this->reserve_assets_[ret->GetUniqueId()] = ret;
    return ret;
  }

  void Import(std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context)
  {
    for (auto& pair : this->reserve_assets_)
    {
      (*dest)[pair.first] = this->ImportProcess(pair.second, context);
    }
    this->reserve_assets_.clear();
  }

  //アセットが参照しているアセットのロードが行われる為、
  //一括ループではなく１つずつロードした方が安全
  bool ImportOnce(std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context)
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
  bool ImportOnce(T_UINT32 unique_id, std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context)
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

  Entity_* ImportImmediately(const std::string& directory_path, const std::string& file_name, const std::string& extension, std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context)
  {
    AssetInfo* info = nullptr;

    //既に予約済みかどうかチェックする
    T_UINT32 uid = context->GetUniqueIdTable()->GetID(directory_path + file_name);
    auto& itr = this->reserve_assets_.find(uid);
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
      if (!std::find(this->target_extensions_.begin(), this->target_extensions_.end(), extension) != this->target_extensions_.end())
      {
        return nullptr;
      }
      info = AssetInfo::Create(directory_path, file_name, extension, context);
    }
    Entity_* ret = this->ImportProcess(info, context);
    (*dest)[info->GetUniqueId()] = ret;
    return ret;
  }

protected:
  virtual Entity_* ImportProcess(AssetInfo* info, AssetConverterContext* context) = 0;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::vector<std::string> target_extensions_;
  std::unordered_map<T_UINT32, AssetInfo*> reserve_assets_;

};
