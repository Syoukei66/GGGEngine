#pragma once

#include "URI.h"

class AssetMetaData;
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
  inline bool IsTarget(const URI& uri);
  inline bool Reserve(const URI& uri, T_UINT32 source_unique_id, AssetConverterContext* context);

  //�A�Z�b�g���Q�Ƃ��Ă���A�Z�b�g�̃��[�h���s����ׁA
  //�ꊇ���[�v�ł͂Ȃ��P�����[�h�����������S
  bool ImportOnce(std::unordered_map<T_UINT32, SharedRef<Entity_>>* dest, AssetConverterContext* context);
  bool ImportOnce(T_UINT32 unique_id, std::unordered_map<T_UINT32, SharedRef<Entity_>>* dest, AssetConverterContext* context);
  SharedRef<Entity_> ImportImmediately(const URI& uri, AssetConverterContext* context);

protected:
  /*!
   * @brief �A�Z�b�g�̃C���|�[�g������
   * �h���N���X���Ŏ��ۂ̃C���|�[�g�������L�q����B
   */
  virtual SharedRef<Entity_> ImportProcess(AssetMetaData* meta, AssetConverterContext* context) = 0;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::vector<std::string> target_extensions_;
  std::unordered_map<T_UINT32, AssetMetaData*> reserve_assets_;

};

#include <Entity/AssetMetaData.h>
#include <Converter/AssetConverterContext.h>

// =================================================================
// Constructor / Destructor
// =================================================================
template<class Entity_>
inline AssetImporter<Entity_>::AssetImporter(const std::vector<std::string>& extensions)
  : target_extensions_(extensions)
{
}

template<class Entity_>
inline AssetImporter<Entity_>::~AssetImporter() 
{
  for (const auto& pair : this->reserve_assets_)
  {
    delete pair.second;
  }
}

// =================================================================
// Methods
// =================================================================
template<class Entity_>
inline bool AssetImporter<Entity_>::IsTarget(const URI& uri)
{
  return std::find(this->target_extensions_.begin(), this->target_extensions_.end(), uri.GetExtension()) != this->target_extensions_.end();
}

template<class Entity_>
inline bool AssetImporter<Entity_>::Reserve(const URI& uri, T_UINT32 source_unique_id, AssetConverterContext* context)
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
template<class Entity_>
inline bool AssetImporter<Entity_>::ImportOnce(std::unordered_map<T_UINT32, SharedRef<Entity_>>* dest, AssetConverterContext* context)
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

template<class Entity_>
inline bool AssetImporter<Entity_>::ImportOnce(T_UINT32 unique_id, std::unordered_map<T_UINT32, SharedRef<Entity_>>* dest, AssetConverterContext* context)
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

template<class Entity_>
inline SharedRef<Entity_> AssetImporter<Entity_>::ImportImmediately(const URI& uri, AssetConverterContext* context)
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

  const SharedRef<Entity_>& ret = this->ImportProcess(meta, context);
  if (!ret)
  {
    delete meta;
  }
  return ret;
}


