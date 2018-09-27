#include "AssetConverterContext.h"
#include "../Core/CerealIO.h"
#include "Setting.h"
#include "Extensions.h"

// =================================================================
// Constructor / Destructor
// =================================================================
AssetConverterContext::AssetConverterContext(const Setting* setting, AssetConverterManager* converter_manager)
  : setting_(setting)
  , converter_manager_(converter_manager)
{
  this->unique_id_table_ = CerealIO::Json::SafeImport<UniqueIdTable>(FileUtil::GetUniqueIdTablePath().c_str());
  if (!this->unique_id_table_)
  {
    this->unique_id_table_ = new UniqueIdTable();
  }
}

AssetConverterContext::~AssetConverterContext()
{
  CerealIO::Json::Export(FileUtil::GetUniqueIdTablePath().c_str(), this->unique_id_table_);
  delete this->unique_id_table_;
}

// =================================================================
// Methods
// =================================================================
AssetInfo* AssetConverterContext::Reserve(const URI& uri)
{
  //���ɃC���|�[�g�ς݂ł���΂���AssetInfo�����^�[��
  const auto& itr = this->infos_.find(this->GetUniqueID(uri));
  if (itr != this->infos_.end())
  {
    return itr->second;
  }

  //Info�����������܂�Converter�𑖍�
  AssetInfo* info = this->converter_manager_->Find<AssetInfo>([&](IAssetConverter* converter)
  {
    return converter->Reserve(uri, this);
  });

  if (info)
  {
    this->infos_[info->GetUniqueID()] = info;
    return info;
  }
  //���^�f�[�^�ȊO�̃t�@�C���őΏۂɂȂ�Ȃ������ꍇ�̓X�L�b�v
  if (uri.GetExtension() != Extensions::META)
  {
    std::cout << "skip \"" << uri.GetFullPath() << "\" " << std::endl;
  }
  return nullptr;
}
