#pragma once

#include <set>
#include <URI.h>
#include "AssetDataContainer.h"
#include "AssetMetaData.h"

class AssetConverterContext;
class AssetConverter;

/*!
 * @brief AssetConverter�ň���Asset�̎���
 */
class AssetEntity : public GGObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(AssetEntity);
  GG_CREATE_FUNC_1(AssetEntity, AssetMetaData*);
  GG_CREATE_FUNC_2(AssetEntity, AssetMetaData*, IAssetDataContainer*);

public:
  template <class AssetData_>
  inline static SharedRef<AssetEntity> Create(AssetMetaData* meta, AssetData_* data)
  {
    // �L���X�g�͏z�Q�Ɖ���̈�
    return AssetEntity::Create(meta, (IAssetDataContainer*)new AssetDataContainer<AssetData_>(data));
  }

  GG_DESTRUCT_FUNC(AssetEntity);

  // =================================================================
  // Methods
  // =================================================================
public:
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
   * �Ώۂ̃A�Z�b�g�̃L���b�V�����C���|�[�g�B
   * �ˑ��֌W�Ȃǂ͂��ł�MetaData�ɋL�^����Ă�����̂Ƃ���
   * @param context
   * @return �L���b�V�������݂��Ȃ����false
   */
  bool ImportFromCache(AssetConverterContext* context);

  /*!
   * @brief ���g���Ǘ����Ă���f�[�^�ɕύX���������ꍇ
   * AssetManager���փA�Z�b�g�̍ēo�^���s��
   */
  void CommitChanges(AssetConverterContext* context);

  /*!
   * @brief ���g���Q�Ƃ��Ă���A�Z�b�g�ɕύX�����邩���ׁA
   * �ύX���������ꍇ�^�C���X�^���v���X�V���Aupdate_entities�ɒǉ����A�_�[�e�B�t���O�𗧂Ă�
   */
  void CheckAssetChanged(AssetConverterContext* context, std::set<SharedRef<AssetEntity>>* update_entities);

  /*!
   * @brief ���g���Q�Ƃ��Ă���T�u�A�Z�b�g�ɕύX�����邩���ׁA
   * �ύX���������ꍇ�_�[�e�B�t���O�𗧂Ă�
   * MEMO: �{����CheckAssetChanged�ōs���Ă����������������A
   * �^�C���X�^���v�̊Ď��Ɠ����ɃT�u�A�Z�b�g�̑������s���ƁA
   * ������Q�Ƃ���Ă�A�Z�b�g���������ꍇ��
   * �`�F�b�N�̃^�C�~���O�̃Y���ɂ��s�������������鎖������ׁA�����𕪊�����
   */
  bool CheckSubAssetChanged(AssetConverterContext* context);

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

  void SetData(IAssetDataContainer* data);

  template <class AssetData_>
  void SetData(AssetData_* data)
  {
    this->SetData((IAssetDataContainer*)new AssetDataContainer<AssetData_>(data));
  }

  template <class AssetData_>
  inline const AssetData_* GetData() const
  {
    return ((AssetDataContainer<AssetData_>*)this->data_)->GetData();
  }

  inline IAssetDataContainer* GetDataContainer()
  {
    return this->data_;
  }

  AssetConverter* GetConverter(AssetConverterContext* context);

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetMetaData* meta_data_;
  AssetConverter* converter_;
  IAssetDataContainer* data_;
  bool is_need_commit_;
  std::unordered_map<T_UINT32, std::string> sub_asset_import_time_stamps_;

};