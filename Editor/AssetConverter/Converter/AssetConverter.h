#pragma once

#include <Entity/AssetEntity.h>
#include <Scene/AssetViewer/AssetViewerBehavior.h>

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
   * @brief URI���\���t�@�C����Converter�ɑΉ����Ă��邩�`�F�b�N����
   * @param uri �t�@�C����URI
   * @return �Ή����Ă����true
   */
  bool IsTarget(const URI& uri) const;

  /*!
   * @brief AssetConverter���ŐV�����C���X�^���X���쐬���鎖���\���`�F�b�N����
   * @return �\�Ȃ�true
   */
  virtual bool CanCreateNewInstance() const = 0;

  /*!
   * @brief ���^�f�[�^����A�Z�b�g���C���|�[�g���A���ԃf�[�^��߂�l�ŕԂ�
   * @param entity AssetEntity
   * @param context AssetConverterContext
   * @return ���ԃf�[�^
   */
  IAssetDataContainer* ImportImmediately(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const;

  /*!
   * @brief �L���b�V������A�Z�b�g���C���|�[�g���A���ԃf�[�^��߂�l�ŕԂ�
   * @param entity AssetEntity
   * @param context AssetConverterContext
   * @return ���ԃf�[�^
   */
  virtual IAssetDataContainer* ImportFromCache(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const = 0;

  /*!
   * @brief �A�Z�b�g���G�N�X�|�[�g����B
   * @param entity AssetEntity
   * @param context AssetConverterContext
   */
  void ExportImmediately(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) const;

  /*!
   * @brief .h�v���O�������o�͂���
   * @param entities AssetEntity�ꗗ
   * @param dest �v���O�����������ݐ�
   */
  void CreateHeaderProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string* dest) const;

  /*!
   * @brief .cpp�v���O�������o�͂���
   * @param entities AssetEntity�ꗗ
   * @param dest �v���O�����������ݐ�
   */
  void CreateCppProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string* dest) const;

  /*!
   * @brief AssetManager�ɃA�Z�b�g��o�^����
   * @param entity AssetEntity
   */
  virtual void RegisterAssetManager(const SharedRef<AssetEntity>& entity) const = 0;

  /*!
   * @brief �V�����C���X�^���X���쐬���A�ۑ�����
   * @return ����������true
   */
  virtual bool CreateNewInstance(const URI& uri) const = 0;

  /*!
   * @brief AssetConverter�ŗL�̐ݒ�N���X�𐶐����A�߂�l�Ƃ��ĕԂ��B
   */
  virtual std::unique_ptr<ConverterSetting> CreateSetting() const = 0;

  /*!
   * @brief �g�p����AssetViewerBehavior���쐬����
   * @return 
   */
  virtual SharedRef<AssetViewerBehavior> CreateViewerBehavior() const = 0;

  /*!
   * @brief �����Ŏw�肵��Asset�N���X���̃A�Z�b�g�ɕϊ�����Converter�Ȃ̂����m���߂�
   * @param asset_name Asset�N���X��
   * @return �ϊ���Asset�N���X���ƈ�v���Ă����true
   */
  virtual bool IsTargetAsset(const std::string& asset_name) const = 0;

  /*!
   * @brief �e���v���[�g�����Ŏw�肵��Asset�N���X�ɕϊ�����Converter�Ȃ̂����m���߂�
   * @return �ϊ���Asset�N���X�ƈ�v���Ă����true
   */
  template <class Asset_>
  bool IsTargetAsset() const
  {
    return this->IsTargetAsset(Asset_::ObjectName());
  }

protected:
  /*!
   * @brief �A�Z�b�g�̃C���|�[�g������
   * �h���N���X���Ŏ��ۂ̃C���|�[�g�������L�q����B
   * @return nullptr��A���݂�DataContainer�Ɠ���DataContainer��Ԃ��Ă�����
   */
  virtual IAssetDataContainer* ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const = 0;

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

  inline const std::vector<std::string>& GetTargetExtensions() const
  {
    return this->target_extensions_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string id_;
  std::vector<std::string> target_extensions_;
  AssetProgramGenerator* program_generator_;

};
