#pragma once

#include <Util/FileUtil.h>

#include <Cereal/cereal.hpp>
#include <Cereal/archives/json.hpp>
#include <Cereal/types/string.hpp>
#include <Cereal/types/unordered_set.hpp>
#include <Cereal/types/utility.hpp>

#include "URI.h"
#include "ConverterSetting.h"

class AssetConverter;
class AssetConverterContext;

class AssetMetaData
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static AssetMetaData* Create(const URI& uri, AssetConverterContext* context);
  static AssetMetaData* Create(const URI& uri, AssetConverter* converter, AssetConverterContext* context);
  static AssetMetaData* Create(const URI& uri, T_UINT32 source_unique_id, AssetConverterContext* context);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetMetaData(const URI& uri, T_UINT32 source_unique_id, AssetConverterContext* context);
  AssetMetaData() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  void Save();

  void ResetTimeStamp();

  /*!
   * @brief ���^�f�[�^���Ή�����f�[�^�̃^�C���X�^���v���X�V����
   * @return �^�C���X�^���v�ɍX�V���������ꍇtrue
   */
  bool UpdateTimeStamp();

  /*!
   * @brief �Ō�ɃC���|�[�g�������Ԃ̃^�C���X�^���v���X�V����
   */
  void UpdateLastImportTimeStamp();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline T_UINT32 GetUniqueID() const
  {
    return this->unique_id_;
  }

  inline T_UINT32 GetSourceUniqueId() const
  {
    return this->source_unique_id_;
  }

  inline const std::string& GetTimeStamp() const
  {
    return this->time_stamp_;
  }

  inline const std::string& GetLastImportTimeStamp()
  {
    return this->last_import_time_stamp_;
  }

  inline const URI& GetURI() const
  {
    return this->uri_;
  }

  inline void SetConverterSetting(std::unique_ptr<ConverterSetting>&& setting)
  {
    this->converter_setting_.reset(setting.release());
  }

  inline const std::unique_ptr<ConverterSetting>& GetConverterSetting()
  {
    return this->converter_setting_;
  }

  inline std::string GetInputPath() const
  {
    return FileUtil::CreateInputPath(this->GetURI());
  }
  
  inline std::string GetInputDirectoryPath() const
  {
    return FileUtil::CreateInputDirectoryPath(this->GetURI());
  }

  inline std::string GetOutputPath() const
  {
    return FileUtil::CreateArchivePath(this);
  }

  // =================================================================
  // Serialize Method
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(CEREAL_NVP(uri_));
    ar(CEREAL_NVP(time_stamp_));
    ar(CEREAL_NVP(last_import_time_stamp_));

    ar(CEREAL_NVP(unique_id_));
    ar(CEREAL_NVP(source_unique_id_));
    ar(CEREAL_NVP(converter_setting_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  /*!
   * @brief �ΏۃA�Z�b�g��URI
   */
  URI uri_;

  /*!
   * @brief �ΏۃA�Z�b�g�̃^�C���X�^���v
   */
  std::string time_stamp_;
  
  /*!
   * @brief �Ō�ɃC���|�[�g�������Ԃ̃^�C���X�^���v
   */
  std::string last_import_time_stamp_;

  /*!
   * @brief �ΏۃA�Z�b�g��UniqueID
   */
  T_UINT32 unique_id_;

  /*!
   * @brief �ΏۃA�Z�b�g�𐶐������A�Z�b�g��UniqueID
   */
  T_UINT32 source_unique_id_;

  /*!
   * @brief ���ݐݒ肵�Ă���ΏۃA�Z�b�g��Converter�̐ݒ�
   */
  std::unique_ptr<ConverterSetting> converter_setting_;

};
