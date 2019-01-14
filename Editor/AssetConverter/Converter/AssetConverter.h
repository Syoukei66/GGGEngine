#pragma once

#include <Entity/AssetImporter.h>
#include <Entity/AssetExporter.h>
#include <ProgramGenerator/AssetProgramGenerator.h>

class AssetConverter 
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverter(
    const std::string& id,
    AssetImporter* importer,
    AssetExporter* exporter,
    AssetProgramGenerator* program_generator
  );

  virtual ~AssetConverter();

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief ���^�f�[�^����A�Z�b�g���C���|�[�g���A���ԃf�[�^��߂�l�ŕԂ�
   * @param meta_data ���^�f�[�^
   * @param context AssetConverterContext
   * @return ���ԃf�[�^
   */
  void* ImportImmediately(AssetMetaData* meta_data, AssetConverterContext* context);

  /*!
   * @brief �A�Z�b�g���G�N�X�|�[�g����B
   * @param entity AssetEntity
   * @param context AssetConverterContext
   */
  void ExportImmediately(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) const;

  /*!
   * @brief �v���O�������o�͂���
   * @param entities AssetEntity�ꗗ
   * @param header header�t�@�C���v���O�����������ݐ�
   * @param cpp cpp�t�@�C���v���O�����������ݐ�
   */
  void CreateProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string* header, std::string* cpp) const;

  /*!
   * @brief AssetManager�ɃA�Z�b�g��o�^����
   * @param entity AssetEntity
   */
  virtual void RegisterAssetManager(const SharedRef<AssetEntity>& entity) = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const std::string& GetId() const
  {
    return this->id_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string id_;
  AssetImporter* importer_;
  AssetExporter* exporter_;
  AssetProgramGenerator* program_generator_;

};
