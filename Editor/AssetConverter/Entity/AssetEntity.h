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
  void Import(AssetConverterContext* context);
  bool Reload(AssetConverterContext* context);
  void Export(AssetConverterContext* context);

private:
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

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetMetaData* meta_data_;
  bool is_dirty_;
  void* cache_;

};