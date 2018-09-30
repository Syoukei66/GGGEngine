#include "AssetConverterContext.h"
#include <Core/CerealIO.h>
#include "Setting.h"
#include "Extensions.h"

// =================================================================
// Constructor / Destructor
// =================================================================
AssetConverterContext::AssetConverterContext(UniqueIdTable* unique_id_table, AssetConverterManager* converter_manager)
  : unique_id_table_(unique_id_table)
  , converter_manager_(converter_manager)
  , infos_()
{
}

AssetConverterContext::~AssetConverterContext()
{
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
