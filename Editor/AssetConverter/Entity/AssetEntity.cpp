#include <Entity/AssetEntity.h>
#include <Entity/AssetMetaData.h>
#include <Converter/AssetConverter.h>
#include <Converter/AssetConverterContext.h>
#include <Util/Logger.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(AssetEntity, AssetMetaData* meta)
{
  this->meta_data_ = meta;
  this->is_need_commit_ = true;
  return true;
}

GG_INIT_FUNC_IMPL_2(AssetEntity, AssetMetaData* meta, IAssetDataContainer* data)
{
  this->meta_data_ = meta;
  this->SetData(data);
  return true;
}

GG_DESTRUCT_FUNC_IMPL(AssetEntity)
{
  delete this->meta_data_;
  delete this->data_;
  return true;
}

// =================================================================
// Methods
// =================================================================
bool AssetEntity::Load(AssetConverterContext* context)
{
  std::set<SharedRef<AssetEntity>> changed_entities_ = std::set<SharedRef<AssetEntity>>();

  // ConverterSetting��������΃��[�h�����͍s��Ȃ�
  if (!this->meta_data_->GetConverterSetting())
  {
    return false;
  }

  // �A�Z�b�g�ɕύX�����邩���o
  this->CheckAssetChanged(context, &changed_entities_);
  if (changed_entities_.size() > 0)
  {
    // �ύX���������A�Z�b�g���C���|�[�g������
    for (const SharedRef<AssetEntity>& entity : changed_entities_)
    {
      entity->Import(context);
    }
  }    
  // �T�u�A�Z�b�g�̕ύX�����o
  if (this->CheckSubAssetChanged(context))
  {
    // AssetEntity�����t���b�V�����A�V�[���̃����[�h���s��
    this->CommitChanges(context);
    return true;
  }
  return false;
}

void AssetEntity::Export(AssetConverterContext* context)
{
  AssetConverter* converter = this->GetConverter(context);
  //TODO: ���ԃf�[�^���ŐV�̂��̂��`�F�b�N���A�ŐV�łȂ�������C���|�[�g���鏈��������
  converter->ExportImmediately(SharedRef<AssetEntity>(this), context);
}

void AssetEntity::ClearCache()
{
  this->SetData(nullptr);
}

void AssetEntity::Import(AssetConverterContext* context)
{
  Logger::ImportAssetLog(this->meta_data_->GetURI());
  AssetConverter* converter = this->GetConverter(context);
  this->SetData(converter->ImportImmediately(SharedRef<AssetEntity>(this), context));
  this->is_need_commit_ = true;
}

bool AssetEntity::ImportFromCache(AssetConverterContext* context)
{
  Logger::ImportFromCacheAssetLog(this->meta_data_->GetURI());
  AssetConverter* converter = this->GetConverter(context);
  IAssetDataContainer* data = converter->ImportFromCache(SharedRef<AssetEntity>(this), context);
  if (!data)
  {
    return false;
  }
  this->SetData(data);
  this->is_need_commit_ = true;
  return true;
}

void AssetEntity::CommitChanges(AssetConverterContext* context)
{
  const std::unique_ptr<ConverterSetting>& setting = this->meta_data_->GetConverterSetting();
  const std::unordered_set<T_UINT32>& sub_asset_uids = setting->GetSubAssetUniqueIds();

  // ���̃R�~�b�g�ł̃T�u�A�Z�b�g�̃C���|�[�g�^�C���X�^���v���擾
  this->sub_asset_import_time_stamps_.clear();
  for (T_UINT32 uid : sub_asset_uids)
  {
    const SharedRef<AssetEntity>& entity = context->GetEntity(uid);
    entity->CommitChanges(context);
    this->sub_asset_import_time_stamps_[uid] = entity->GetMetaData()->GetLastImportTimeStamp();
  }
  if (this->is_need_commit_)
  {
    Logger::CommitAssetLog(this->meta_data_);
    AssetConverter* converter = context->GetConverter(setting->GetConverterID());
    converter->RegisterAssetManager(SharedRef<AssetEntity>(this));
    this->is_need_commit_ = false;
  }
}

void AssetEntity::CheckAssetChanged(AssetConverterContext* context, std::set<SharedRef<AssetEntity>>* update_entities)
{
  bool dirty_self = false;

  // �^�C���X�^���v���X�V����Ă�����
  if (this->meta_data_->UpdateTimeStamp())
  {
    // ���^�f�[�^��ۑ����A�_�[�e�B�t���O�𗧂Ă�
    this->meta_data_->Save();
    dirty_self = true;
  }
  
  // ConverterSetting��������Ή����s��Ȃ�
  if (!this->meta_data_->GetConverterSetting())
  {
    return;
  }

  // ConverterSetting�ɕύX����������_�[�e�B�t���O�𗧂Ă�
  if (this->meta_data_->GetConverterSetting()->IsDirty())
  {
    dirty_self = true;
  }

  // SourceAsset�����l�ɒ�������
  const SharedRef<AssetEntity>& source = context->GetEntity(this->meta_data_->GetSourceUniqueId());
  bool dirty_source = false;

  // �^�C���X�^���v���X�V����Ă�����
  if (source->GetMetaData()->UpdateTimeStamp())
  {
    // ���^�f�[�^��ۑ����A�_�[�e�B�t���O�𗧂Ă�
    source->GetMetaData()->Save();
    dirty_source = true;
  }
  
  // ConverterSetting�ɕύX����������_�[�e�B�t���O�𗧂Ă�
  if (source->GetMetaData()->GetConverterSetting()->IsDirty())
  {
    dirty_source = true;
  }

  // ���ԃf�[�^�����݂��Ă��炸�A
  // �_�[�e�B�t���O�������Ă��Ȃ���΃L���b�V�����E���Ă���
  if (!this->data_ && !dirty_self && !dirty_source)
  {
    // �L���b�V������̓ǂݍ��݂����s�����Ȃ�_�[�e�B�t���O�𗧂Ă�
    if (!this->ImportFromCache(context))
    {
      dirty_self = true;
    }
  }
  
  // �_�[�e�B�t���O�������Ă�����update_entities��UniqueId��ǉ�����
  if (dirty_self)
  {
    update_entities->insert(SharedRef<AssetEntity>(this));
  }

  // �_�[�e�B�t���O�������Ă�����update_entities�Ƀ\�[�XUniqueId��ǉ�����
  if (dirty_source)
  {
    update_entities->insert(source);
  }

  // �܂��`�F�b�N���Ă��Ȃ��T�u�A�Z�b�g�������
  const std::unordered_set<T_UINT32>& sub_asset_uids = this->meta_data_->GetConverterSetting()->GetSubAssetUniqueIds();
  for (T_UINT32 uid : sub_asset_uids)
  {
    context->GetEntity(uid)->CheckAssetChanged(context, update_entities);
  }
}

bool AssetEntity::CheckSubAssetChanged(AssetConverterContext* context)
{
  const std::unordered_set<T_UINT32>& sub_asset_uids = this->meta_data_->GetConverterSetting()->GetSubAssetUniqueIds();
  for (T_UINT32 uid : sub_asset_uids)
  {
    const SharedRef<AssetEntity>& entity = context->GetEntity(uid);
    // (1)
    // �O��̃R�~�b�g���ƃT�u�A�Z�b�g�̃C���|�[�g�^�C���X�^���v��
    // �Ⴂ������΃R�~�b�g�����Ȃ����K�v������B
    if (!this->is_need_commit_)
    {
      // �C���|�[�g�^�C���X�^���v���L�^����Ă��邩���ׂ�
      const auto& itr = this->sub_asset_import_time_stamps_.find(uid);
      if (itr == this->sub_asset_import_time_stamps_.end())
      {
        // �L�^����Ă��Ȃ���΃R�~�b�g���K�v
        this->is_need_commit_ = true;
      }
      else
      {
        // �L�^����Ă��邪�Ⴂ���������ꍇ���R�~�b�g���K�v
        if (itr->second != entity->GetMetaData()->GetLastImportTimeStamp())
        {
          this->is_need_commit_ = true;
        }
      }
    }
    this->sub_asset_import_time_stamps_[uid] = entity->GetMetaData()->GetLastImportTimeStamp();

    // (2)
    // �T�u�A�Z�b�g�ɃR�~�b�g������Ύ��g���R�~�b�g����K�v������B
    this->is_need_commit_ |= context->GetEntity(uid)->CheckSubAssetChanged(context);
  }

  // �Ăяo����Ɏ��g�̃R�~�b�g�̗L����`����
  return this->is_need_commit_;
}

// =================================================================
// Getter / Setter
// =================================================================
void AssetEntity::SetData(IAssetDataContainer* data)
{
  if (this->data_ == data)
  {
    return;
  }
  if (this->data_)
  {
    delete this->data_;
  }
  this->data_ = data;
  if (!this->data_)
  {
    return;
  }
  this->data_->SaveCache(this->meta_data_->GetURI());
  this->meta_data_->UpdateLastImportTimeStamp();
  this->is_need_commit_ = true;
}

AssetConverter* AssetEntity::GetConverter(AssetConverterContext* context) const
{
  const std::unique_ptr<ConverterSetting>& setting = this->meta_data_->GetConverterSetting();
  if (!setting)
  {
    return nullptr;
  }
  return context->GetConverter(setting->GetConverterID());
}
