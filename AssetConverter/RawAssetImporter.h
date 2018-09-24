#pragma once

#include "AssetImporter.h"
#include "RawAssetEntity.h"

//���f�[�^������ɕϊ��Ȃǂ��s���Ȃ��A�Z�b�g�̃C���|�[�^�\
class RawAssetImporter : public AssetImporter<RawAssetEntity>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  RawAssetImporter(const std::vector<std::string>& extensions);

  // =================================================================
  // Methods
  // =================================================================
protected:
  RawAssetEntity* ImportProcess(AssetInfo* info, AssetConverterContext* context) override;

};
