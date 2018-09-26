#include "AssetConverterContext.h"
#include "../Core/CerealIO.h"
#include "Setting.h"

// =================================================================
// Constructor / Destructor
// =================================================================
AssetConverterContext::AssetConverterContext(const Setting* setting, AssetConverterManager* converter_manager)
  : setting_(setting)
  , converter_manager_(converter_manager)
{
  this->unique_id_table_ = CerealIO::Binary::SafeImport<UniqueIdTable>(setting->unique_id_table_path.c_str());
  if (!this->unique_id_table_)
  {
    this->unique_id_table_ = new UniqueIdTable();
  }
}

AssetConverterContext::~AssetConverterContext()
{
  delete this->unique_id_table_;
}

// =================================================================
// Methods
// =================================================================
AssetInfo* AssetConverterContext::Reserve(const URI& uri)
{
  //既にインポート済みであればそのAssetInfoをリターン
  const auto& itr = this->infos_.find(this->PublishUniqueID(uri));
  if (itr != this->infos_.end())
  {
    return itr->second;
  }

  //Infoが生成されるまでConverterを走査
  AssetInfo* info = this->converter_manager_->Find<AssetInfo>([&](IAssetConverter* converter)
  {
    return converter->Reserve(uri, this);
  });

  if (info)
  {
    this->infos_[info->GetUniqueID()] = info;
    return info;
  }
  //対象にならなかった場合はスキップ
  std::cout << "skip \"" << uri.GetFullPath() << "\" " << std::endl;
  return nullptr;
}
