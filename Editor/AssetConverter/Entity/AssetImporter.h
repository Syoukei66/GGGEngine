#pragma once

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
  inline bool IsTarget(const URI& uri);
  inline bool Reserve(const URI& uri, const URI& source, AssetConverterContext* context);

  void Import(std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context);
  //�A�Z�b�g���Q�Ƃ��Ă���A�Z�b�g�̃��[�h���s����ׁA
  //�ꊇ���[�v�ł͂Ȃ��P�����[�h�����������S
  bool ImportOnce(std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context);
  bool ImportOnce(T_UINT32 unique_id, std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context);
  Entity_* ImportImmediately(const URI& uri, AssetConverterContext* context);

protected:
  /*!
   * @brief �A�Z�b�g�̃C���|�[�g������
   * �h���N���X���Ŏ��ۂ̃C���|�[�g�������L�q����B
   */
  virtual Entity_* ImportProcess(AssetInfo* info, AssetConverterContext* context) = 0;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::vector<std::string> target_extensions_;
  std::unordered_map<T_UINT32, AssetInfo*> reserve_assets_;

};

#include <Entity/AssetInfo.h>
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
inline AssetImporter<Entity_>::~AssetImporter() {}

// =================================================================
// Methods
// =================================================================
template<class Entity_>
inline bool AssetImporter<Entity_>::IsTarget(const URI& uri)
{
  return std::find(this->target_extensions_.begin(), this->target_extensions_.end(), uri.GetExtension()) != this->target_extensions_.end();
}

template<class Entity_>
inline bool AssetImporter<Entity_>::Reserve(const URI& uri, const URI& source, AssetConverterContext* context)
{
  //�Ή�����g���q���`�F�b�N
  if (!this->IsTarget(uri))
  {
    return false;
  }
  AssetInfo* info = AssetInfo::Create(uri, source, context);
  this->reserve_assets_[info->GetUniqueID()] = info;
  return true;
}

template<class Entity_>
inline void AssetImporter<Entity_>::Import(std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context)
{
  for (auto& pair : this->reserve_assets_)
  {
    (*dest)[pair.first] = this->ImportProcess(pair.second, context);
  }
  this->reserve_assets_.clear();
}

//�A�Z�b�g���Q�Ƃ��Ă���A�Z�b�g�̃��[�h���s����ׁA
//�ꊇ���[�v�ł͂Ȃ��P�����[�h�����������S
template<class Entity_>
inline bool AssetImporter<Entity_>::ImportOnce(std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context)
{
  const auto& begin = this->reserve_assets_.begin();
  if (begin == this->reserve_assets_.end())
  {
    return false;
  }
  T_UINT32 unique_id = begin->first;
  AssetInfo* info = begin->second;
  this->reserve_assets_.erase(begin->first);
  //�C�e���[�^�[�������I��������Import�������s������
  //���荞�݂��������Ă����S�ɏ����ł���
  Logger::ImportAssetLog(info->GetURI()); 
  (*dest)[unique_id] = this->ImportProcess(info, context);
  return true;
}

template<class Entity_>
inline bool AssetImporter<Entity_>::ImportOnce(T_UINT32 unique_id, std::unordered_map<T_UINT32, Entity_*>* dest, AssetConverterContext* context)
{
  const auto& itr = this->reserve_assets_.find(unique_id);
  if (itr == this->reserve_assets_.end())
  {
    return false;
  }
  AssetInfo* info = itr->second;
  this->reserve_assets_.erase(itr->first);
  //�C�e���[�^�[�������I��������Import�������s������
  //���荞�݂��������Ă����S�ɏ����ł���
  std::cout << "importing \"" << info->GetURI().GetFullPath() << "\" " << std::endl;
  (*dest)[unique_id] = this->ImportProcess(info, context);
  return true;
}

template<class Entity_>
inline Entity_* AssetImporter<Entity_>::ImportImmediately(const URI& uri, AssetConverterContext* context)
{
  AssetInfo* info = nullptr;

  //���ɗ\��ς݂��ǂ����`�F�b�N����
  T_UINT32 uid = context->GetUniqueID(uri);
  const auto& itr = this->reserve_assets_.find(uid);
  if (itr != this->reserve_assets_.end())
  {
    info = itr->second;
    //�\����������Ƃ�
    this->reserve_assets_.erase(itr);
  }
  //�\��ς݂���Ȃ�������AssetInfo�����Ƃ��납��
  else
  {
    //�Ή�����g���q���`�F�b�N
    if (!IsTarget(uri))
    {
      return nullptr;
    }
    info = AssetInfo::Create(uri, uri, context);
  }
  return this->ImportProcess(info, context);
}


