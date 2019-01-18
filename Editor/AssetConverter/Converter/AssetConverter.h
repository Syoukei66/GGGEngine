#pragma once

#include <Entity/AssetEntity.h>

class AssetProgramGenerator;

class AssetConverter 
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverter(
    const std::string& id,
    const std::string& class_name,
    const std::vector<std::string>& extensions,
    T_UINT32 skip_head, T_UINT32 skip_tail
  );

  virtual ~AssetConverter();

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * URI���\���t�@�C����Converter�ɑΉ����Ă��邩�`�F�b�N����
   * @param uri �t�@�C����URI
   * @return �Ή����Ă����true
   */
  bool IsTarget(const URI& uri) const;

  /*!
   * @brief ���^�f�[�^����A�Z�b�g���C���|�[�g���A���ԃf�[�^��߂�l�ŕԂ�
   * @param meta_data ���^�f�[�^
   * @param context AssetConverterContext
   * @return ���ԃf�[�^
   */
  IAssetDataContainer* ImportImmediately(AssetMetaData* meta_data, AssetConverterContext* context) const;

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
  virtual void RegisterAssetManager(const SharedRef<AssetEntity>& entity) const = 0;

  /*!
   * @brief AssetConverter�ŗL�̐ݒ�N���X�𐶐����A�߂�l�Ƃ��ĕԂ��B
   */
  virtual std::unique_ptr<ConverterSetting> CreateSetting() const = 0;

protected:
  /*!
   * @brief �A�Z�b�g�̃C���|�[�g������
   * �h���N���X���Ŏ��ۂ̃C���|�[�g�������L�q����B
   */
  virtual IAssetDataContainer* ImportProcess(AssetMetaData* meta, AssetConverterContext* context) const = 0;

  /*!
   * @brief �A�Z�b�g�̃C���|�[�g������
   * �h���N���X���Ŏ��ۂ̃G�N�X�|�[�g�������L�q����B
   */
  virtual void ExportProcess(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) const = 0;

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
  std::vector<std::string> target_extensions_;
  AssetProgramGenerator* program_generator_;

};
