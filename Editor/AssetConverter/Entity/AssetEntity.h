#pragma once

#include <set>
#include <URI.h>

class AssetMetaData;

#define ENTITY_ID(id) public:\
enum { ID = id };\
virtual T_UINT32 GetID() const override\
{\
  return ID;\
}

class AssetEntity : public GGObject
{
public:
  enum EntityID
  {
    ID_DEFAULT_MESH,
    ID_DEFAULT_MATERIAL,
    ID_TEXTURE,
    ID_CSV,
    ID_JSON,
    ID_SHADER,
    ID_SOUND,
    ID_MODEL_MESH,
    ID_MODEL_MATERIAL,
    ID_STATIC_MODEL,
    ID_CHARACTER_MODEL,
  };

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_INIT_FUNC_1(AssetEntity, AssetMetaData*);
  GG_DESTRUCT_FUNC(AssetEntity);

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief ���g���Ǘ����Ă���f�[�^�ɕύX���������ꍇ
   * AssetManager���փA�Z�b�g�̍ēo�^���s��
   */
  void CommitChanges();

  /*!
   * @brief ���g��Q�Ƃ��Ă���A�Z�b�g�Q�ɕύX�����邩���ׁA
   * �ύX���������ꍇ�A�b�v�f�[�g����B
   */
  void CheckChanged(std::set<SharedRef<AssetEntity>>* update_entities);

  /*!
   * @brief �Q�Ƃ��Ă���A�Z�b�g��ǉ�����
   */
  void AddReferencedEntity(const SharedRef<AssetEntity>& entity);

protected:
  /*!
   * @brief �������Ǘ����Ă��郊�\�[�X��AssetManager�֏㏑���o�^����
   */
  virtual void RegisterAssetManager(T_UINT32 uid, const std::string& extension) const = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual T_UINT32 GetID() const = 0;

  inline AssetMetaData* GetMetaData() const
  {
    return this->meta_data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetMetaData* meta_data_;
  std::vector<SharedRef<AssetEntity>> referenced_entities_;

};