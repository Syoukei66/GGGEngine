#pragma once

#include "URI.h"

class AssetMetaData;
class AssetConverterContext;

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
  bool ImportOnce(std::unordered_map<T_UINT32, SharedRef<AssetEntity>>* dest, AssetConverterContext* context);
  bool ImportOnce(T_UINT32 unique_id, std::unordered_map<T_UINT32, SharedRef<AssetEntity>>* dest, AssetConverterContext* context);
  SharedRef<AssetEntity> ImportImmediately(const URI& uri, AssetConverterContext* context);

protected:
  /*!
   * @brief �A�Z�b�g�̃C���|�[�g������
   * �h���N���X���Ŏ��ۂ̃C���|�[�g�������L�q����B
   */
  virtual SharedRef<AssetEntity> ImportProcess(AssetMetaData* meta, AssetConverterContext* context) = 0;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::vector<std::string> target_extensions_;
  std::unordered_map<T_UINT32, AssetMetaData*> reserve_assets_;

};
