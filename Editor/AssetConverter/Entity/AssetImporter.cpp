#include "AssetImporter.h"
#include <Entity/AssetMetaData.h>
#include <Converter/AssetConverterContext.h>

// =================================================================
// Constructor / Destructor
// =================================================================
AssetImporter::AssetImporter(const std::vector<std::string>& extensions)
  : target_extensions_(extensions)
{
}

AssetImporter::~AssetImporter()
{
  for (const auto& pair : this->reserve_assets_)
  {
    delete pair.second;
  }
}

// =================================================================
// Methods
// =================================================================
bool AssetImporter::IsTarget(const URI& uri)
{
  return std::find(this->target_extensions_.begin(), this->target_extensions_.end(), uri.GetExtension()) != this->target_extensions_.end();
}

bool AssetImporter::Reserve(const URI& uri, T_UINT32 source_unique_id, AssetConverterContext* context)
{
  //対応する拡張子かチェック
  if (!this->IsTarget(uri))
  {
    return false;
  }
  AssetMetaData* meta = AssetMetaData::Create(uri, source_unique_id, context);
  this->reserve_assets_[meta->GetUniqueID()] = meta;
  return true;
}

//アセットが参照しているアセットのロードが行われる為、
//一括ループではなく１つずつロードした方が安全
bool AssetImporter::ImportOnce(std::unordered_map<T_UINT32, SharedRef<AssetEntity>>* dest, AssetConverterContext* context)
{
  const auto& begin = this->reserve_assets_.begin();
  if (begin == this->reserve_assets_.end())
  {
    return false;
  }
  T_UINT32 unique_id = begin->first;
  AssetMetaData* meta = begin->second;
  this->reserve_assets_.erase(begin->first);
  //イテレーター処理が終わった後にImport処理を行う事で
  //割り込みが発生しても安全に処理できる
  Logger::ImportAssetLog(meta->GetURI());
  (*dest)[unique_id] = this->ImportProcess(meta, context);
  return true;
}

bool AssetImporter::ImportOnce(T_UINT32 unique_id, std::unordered_map<T_UINT32, SharedRef<AssetEntity>>* dest, AssetConverterContext* context)
{
  const auto& itr = this->reserve_assets_.find(unique_id);
  if (itr == this->reserve_assets_.end())
  {
    return false;
  }
  AssetMetaData* meta = itr->second;
  this->reserve_assets_.erase(itr->first);
  //イテレーター処理が終わった後にImport処理を行う事で
  //割り込みが発生しても安全に処理できる
  std::cout << "importing \"" << meta->GetURI().GetFullPath() << "\" " << std::endl;
  (*dest)[unique_id] = this->ImportProcess(meta, context);
  return true;
}

SharedRef<AssetEntity> AssetImporter::ImportImmediately(const URI& uri, AssetConverterContext* context)
{
  AssetMetaData* meta = nullptr;

  //既に予約済みかどうかチェックする
  T_UINT32 uid = context->GetUniqueID(uri);
  const auto& itr = this->reserve_assets_.find(uid);
  if (itr != this->reserve_assets_.end())
  {
    meta = itr->second;
    //予約を解除しとく
    this->reserve_assets_.erase(itr);
  }
  //予約済みじゃなかったらAssetMetaDataを作るところから
  else
  {
    //対応する拡張子かチェック
    if (!IsTarget(uri))
    {
      return nullptr;
    }
    meta = AssetMetaData::Create(uri, context);
  }

  const SharedRef<AssetEntity>& ret = this->ImportProcess(meta, context);
  if (!ret)
  {
    delete meta;
  }
  return ret;
}


