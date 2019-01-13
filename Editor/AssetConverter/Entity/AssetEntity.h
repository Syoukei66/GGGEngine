#pragma once

#include <set>
#include <URI.h>

class AssetConverterContext;
class AssetConverter;
class AssetMetaData;

class AssetEntity : public GGObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(AssetEntity);
  GG_CREATE_FUNC_1(AssetEntity, AssetMetaData*);
  GG_DESTRUCT_FUNC(AssetEntity);

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * �쐬�ς݂̃f�[�^�𒼐ڎ󂯎��
   */
  void SetData(void* data);

  /*!
   * ���g���Q�Ƃ��Ă���A�Z�b�g�܂߂đS�ẴA�Z�b�g�����[�h����B
   * ���Ƀ��[�h�ς݂Ȃ牽���s��Ȃ��B
   * @param context
   * @return ���[�h���s��ꂽ�Ȃ�true
   */
  bool Load(AssetConverterContext* context);

  /*!
   * �Ώۂ̃A�Z�b�g��ϊ����A�ϊ���̃f�[�^��
   * �����^�C���p�̃f�B���N�g���Ƀ����^�C���p�̃t�H�[�}�b�g�ŏo�͂���B
   * @param context
   */
  void Export(AssetConverterContext* context);

private:
  /*!
   * �Ώۂ̃A�Z�b�g���C���|�[�g�B
   * �����ɃA�Z�b�g�̈ˑ��֌W���쐬���A
   * ���g���Q�Ƃ��Ă���A�Z�b�g�̃��[�h���s���B
   * @param context
   */
  void Import(AssetConverterContext* context);

  /*!
   * @brief ���g���Ǘ����Ă���f�[�^�ɕύX���������ꍇ
   * AssetManager���փA�Z�b�g�̍ēo�^���s��
   */
  void CommitChanges(AssetConverterContext* context);

  /*!
   * @brief ���g���Q�Ƃ��Ă���A�Z�b�g�ɕύX�����邩���ׁA
   * �ύX���������ꍇ�^�C���X�^���v���X�V���Aupdate_entities�ɒǉ����A�_�[�e�B�t���O�𗧂Ă�
   */
  void CheckAssetChanged(std::set<SharedRef<AssetEntity>>* update_entities);

  /*!
   * @brief ���g���Q�Ƃ��Ă���T�u�A�Z�b�g�ɕύX�����邩���ׁA
   * �ύX���������ꍇ�_�[�e�B�t���O�𗧂Ă�
   * MEMO: �{����CheckAssetChanged�ōs���Ă����������������A
   * �^�C���X�^���v�̊Ď��Ɠ����ɃT�u�A�Z�b�g�̑������s���ƁA
   * ������Q�Ƃ���Ă�A�Z�b�g���������ꍇ��
   * �`�F�b�N�̃^�C�~���O�̃Y���ɂ��s�������������鎖������ׁA�����𕪊�����
   */
  bool CheckSubAssetChanged();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const AssetMetaData* GetMetaData() const
  {
    return this->meta_data_;
  }
  inline AssetMetaData* GetMetaData()
  {
    return this->meta_data_;
  }
  inline const void* GetData() const
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetMetaData* meta_data_;
  bool is_dirty_;
  void* data_;

};