#pragma once

#include "URI.h"

struct Setting;

class AssetConverter;
class AssetConverterManager;
class AssetMetaData;
class UniqueIdTable;
class AssetEntity;

class AssetConverterContext
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverterContext(UniqueIdTable* unique_id_table);
  virtual ~AssetConverterContext();

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief Asset�t�H���_��T�����A���o�^�̃t�@�C��������AssetEntity���쐬����B
   */
  void Fetch();

  /*!
   * @brief �S�Ă�AssetEntity�ɑ΂��ď������s��
   * @param func AssetEntity�ɑ΂��čs������
   */
  void VisitAllEntity(const std::function<void(const SharedRef<AssetEntity>&)>& func);

  /*!
   * @brief AssetEntity��ǉ�����
   * @param entity AssetEntity
   * @return �ǉ�����AssetEntity
   */
  SharedRef<AssetEntity> AddEntity(const SharedRef<AssetEntity>& entity);

  /*!
   * @brief URI����AssetEntity���擾����
   * @param uri URI
   * @return �擾����AssetEntity�B�o�^����Ă��Ȃ��ꍇ��nullptr���A���Ă���B
   */
  SharedRef<AssetEntity> GetEntity(const URI& uri);

  /*!
   * @brief UniqueId����AssetEntity���擾����
   * @param unique_id UniqueId
   * @return �擾����AssetEntity�B�o�^����Ă��Ȃ��ꍇ�̓G���[����������B
   */
  SharedRef<AssetEntity> GetEntity(T_UINT32 unique_id);

  /*!
   * @brief �����𖞂���AssetEntity��S�Ď擾����
   * @param dest ����
   * @param cond ����
   */
  void GetEntities(std::vector<SharedRef<AssetEntity>>* dest, const std::function<bool(const SharedRef<AssetEntity>&)>& cond);

  /*!
   * @brief URI����UniqueId�𔭍s����BURI�̓����^�C������URI�ɕϊ������B
   * ���ɔ��s�ς݂�URI�������ꍇ�͔��s�ς݂̒l��Ԃ��B
   * @param uri �G�f�B�^�ł�URI
   * @return URI���甭�s����UniqueId
   */
  T_UINT32 PublishUniqueID(const URI& uri);

  /*!
   * @brief URI����UniqueId���擾����BURI�̓����^�C������URI�ɕϊ������B
   * ���s����ĂȂ�URI�������ꍇ�̓G���[
   * @param uri �G�f�B�^�ł�URI
   * @return URI����擾����UniqueId
   */
  T_UINT32 GetUniqueID(const URI& uri) const;

  /*!
   * @brief URI���w�肵�ăf�t�H���g�A�Z�b�g��UniqueId��o�^����
   * @param default_uid �f�t�H���g�A�Z�b�g��UniqueId
   * @param uri �f�t�H���g�A�Z�b�g��URI
   */
  void RegisterDefaultUniqueID(T_UINT32 default_uid, const URI& uri);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  /*!
   * @brief �f�t�H���g�A�Z�b�gID����f�t�H���g�A�Z�b�g��URI���擾����
   * @param default_uid �f�t�H���g�A�Z�b�gID
   * @return �f�t�H���g�A�Z�b�g��URI
   */
  inline const URI& GetDefaultAssetURI(T_UINT32 default_uid)
  {
    return this->default_asset_uri_[default_uid];
  }

  /*!
   * @brief AssetConverter��ǉ�����
   * @param converter �ǉ�����AssetConverter
   * @return �ǉ�����AssetConverter
   */
  AssetConverter* AddConverter(AssetConverter* converter);

  /*!
   * @brief DefaultAsset�p��AssetConverter��ǉ�����
   * @param converter �ǉ�����AssetConverter
   * @return �ǉ�����AssetConverter
   */
  AssetConverter* AddDefaultAssetConverter(AssetConverter* converter);

  /*!
   * @brief AssetCovnerterId����AssetConverter���擾����
   * @param id ID
   * @return �w�肵��ID������AssetConverter
   */
  AssetConverter* GetConverter(const std::string& id);

  /*!
   * @brief AssetConverterId����const AssetConverter���擾����
   * @param id ID
   * @return �w�肵��ID������AssetConverter
   */
  const AssetConverter* GetConverter(const std::string& id) const;

  // =================================================================
  // Data Members
  // =================================================================
protected:
  UniqueIdTable* unique_id_table_;
  std::unordered_map<std::string, AssetConverter*> converter_map_;
  std::unordered_map<std::string, AssetConverter*> default_asset_converter_map_;
  std::unordered_map<T_UINT32, URI> default_asset_uri_;
  std::unordered_map<std::string, T_UINT32> default_asset_unique_id_;
  std::unordered_map<T_UINT32, SharedRef<AssetEntity>> asset_entities_;

};
