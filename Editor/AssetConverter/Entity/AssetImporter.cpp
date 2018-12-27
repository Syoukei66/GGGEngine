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
  //�Ή�����g���q���`�F�b�N
  if (!this->IsTarget(uri))
  {
    return false;
  }
  AssetMetaData* meta = AssetMetaData::Create(uri, source_unique_id, context);
  this->reserve_assets_[meta->GetUniqueID()] = meta;
  return true;
}

//�A�Z�b�g���Q�Ƃ��Ă���A�Z�b�g�̃��[�h���s����ׁA
//�ꊇ���[�v�ł͂Ȃ��P�����[�h�����������S
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
  //�C�e���[�^�[�������I��������Import�������s������
  //���荞�݂��������Ă����S�ɏ����ł���
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
  //�C�e���[�^�[�������I��������Import�������s������
  //���荞�݂��������Ă����S�ɏ����ł���
  std::cout << "importing \"" << meta->GetURI().GetFullPath() << "\" " << std::endl;
  (*dest)[unique_id] = this->ImportProcess(meta, context);
  return true;
}

SharedRef<AssetEntity> AssetImporter::ImportImmediately(const URI& uri, AssetConverterContext* context)
{
  AssetMetaData* meta = nullptr;

  //���ɗ\��ς݂��ǂ����`�F�b�N����
  T_UINT32 uid = context->GetUniqueID(uri);
  const auto& itr = this->reserve_assets_.find(uid);
  if (itr != this->reserve_assets_.end())
  {
    meta = itr->second;
    //�\����������Ƃ�
    this->reserve_assets_.erase(itr);
  }
  //�\��ς݂���Ȃ�������AssetMetaData�����Ƃ��납��
  else
  {
    //�Ή�����g���q���`�F�b�N
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


