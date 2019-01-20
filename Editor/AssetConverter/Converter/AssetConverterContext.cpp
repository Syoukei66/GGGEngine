#include "AssetConverterContext.h"
#include "AssetConverter.h"
#include <Core/Application/Asset/UniqueIdTable.h>
#include <Constants/Extensions.h>
#include <Util/Logger.h>

AssetConverterContext::AssetConverterContext(UniqueIdTable* unique_id_table)
  : unique_id_table_(unique_id_table)
{
}

AssetConverterContext::~AssetConverterContext()
{
  for (const auto& pair : this->converter_map_)
  {
    delete pair.second;
  }
}

void AssetConverterContext::Fetch()
{
  // (1)
  // URI����UniqueId���쐬�A
  // uniqueId��asset_entities_�ɓo�^����Ă��Ȃ��t�@�C���������A
  // AssetEntity�����݂��Ȃ��t�@�C����URI���X�g�Ɋi�[
  std::vector<URI> unknown_files = std::vector<URI>();
 
  FileUtil::CrawlInputDirectory([&](const URI& uri)
  {
    // ���^�f�[�^�̓X�L�b�v
    if (uri.GetExtension() == Extensions::META)
    {
      return;
    }
    // AssetEntity�����݂��Ă��Ȃ��t�@�C����unknown_files�ɒǉ�
    const T_UINT32 uid = this->PublishUniqueID(uri.GetFullPath());
    if (this->asset_entities_.find(uid) == this->asset_entities_.end())
    {
      unknown_files.emplace_back(uri);
    }
  });

  // (2)
  // AssetEntity�����݂��Ȃ��t�@�C����URI���X�g����
  // MetaData�����邩�ǂ�����T��
  for (const URI& uri : unknown_files)
  {
    if (FileUtil::IsFileExist((uri.GetFullPath() + "." + Extensions::META).c_str()))
    {
      //TODO: MetaData�����邪�AMetaData����URI�����ۂ�URI�ƑΉ����Ă��Ȃ��t�@�C���ɂ��Ă̏������L�q����B
    }
    // AssetEntity�AMetaData���쐬
    const T_UINT32 uid = this->PublishUniqueID(uri.GetFullPath());
    AssetMetaData* meta_data = AssetMetaData::Create(uri, this);

    // ConverterSetting��������΃f�t�H���g��ConverterSetting��ݒ肷��
    if (!meta_data->GetConverterSetting())
    {
      for (const auto& pair : this->converter_map_)
      {
        if (pair.second->IsTarget(uri))
        {
          meta_data->SetConverterSetting(pair.second->CreateSetting());
          break;
        }
      }
    }

    this->asset_entities_[uid] = AssetEntity::Create(meta_data);
  }

  // UniqueIdTable��ۑ�����
  CerealIO::Json::Export(FileUtil::GetMidDataUniqueIdTablePath().c_str(), this->unique_id_table_);
}

void AssetConverterContext::VisitAllEntity(const std::function<void(const SharedRef<AssetEntity>&)>& func)
{
  for (const auto& pair : this->asset_entities_)
  {
    func(pair.second);
  }
}

SharedRef<AssetEntity> AssetConverterContext::AddEntity(const SharedRef<AssetEntity>& entity)
{
  if (!entity)
  {
    Logger::ConvertFaildLog(entity->GetMetaData());
    return nullptr;
  }
  this->asset_entities_[entity->GetMetaData()->GetUniqueID()] = entity;
  return entity;
}

SharedRef<AssetEntity> AssetConverterContext::GetEntity(const URI& uri)
{
  return this->asset_entities_[this->GetUniqueID(uri.GetFullPath())];
}

SharedRef<AssetEntity> AssetConverterContext::GetEntity(T_UINT32 unique_id)
{
  if (unique_id > DefaultUniqueID::DEFAULT_UID_BEGIN)
  {
    unique_id = this->unique_id_table_->GetDefaultAssetUniqueID(unique_id);
  }
  return this->asset_entities_[unique_id];
}

T_UINT32 AssetConverterContext::PublishUniqueID(const URI& uri)
{
  return this->unique_id_table_->Publish(FileUtil::CreateRuntimeAssetPath(uri));
}

T_UINT32 AssetConverterContext::GetUniqueID(const URI& uri) const
{
  return this->unique_id_table_->GetID(FileUtil::CreateRuntimeAssetPath(uri));
}

void AssetConverterContext::RegisterDefaultUniqueID(T_UINT32 default_uid, const URI& uri)
{
  this->unique_id_table_->RegisterDefaultAssetUniqueID(default_uid, FileUtil::CreateRuntimeAssetPath(uri));
  this->default_asset_uri_[default_uid] = uri;
}

AssetConverter* AssetConverterContext::AddConverter(AssetConverter* converter)
{
  this->converter_map_[converter->GetId()] = converter;
  return converter;
}
