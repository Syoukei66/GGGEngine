#pragma once

#include <Cereal/cereal.hpp>
#include "URI.h"

/*!
 * Converter�̐ݒ�B
 */
class ConverterSetting
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief �f�t�H���g�R���X�g���N�^�B�V���A���C�Y�p
   */
  ConverterSetting() = default;

  ConverterSetting(const std::string& converter_id)
    : converter_id_(converter_id)
    , sub_asset_unique_ids_()
    , is_dirty_(true)
  {}

  virtual ~ConverterSetting() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  inline void AddSubAsset(T_UINT32 uid)
  {
    this->sub_asset_unique_ids_.insert(uid);
  }

  inline void ClearSubAssets()
  {
    this->sub_asset_unique_ids_.clear();
  }

  /*!
   * @brief ImGUI���g���ăf�[�^��ҏW����
   */
  inline void EditWithImGui()
  {
    this->is_dirty_ |= this->EditWithImGuiProcess();
  }

  inline void ClearDirty()
  {
    this->is_dirty_ = false;
  }

protected:
  /*!
   * @brief ImGUI���g���ăf�[�^��ҏW���鏈�����L�q����B
   * @return �f�[�^�ɕύX���������ꍇtrue
   */
  virtual bool EditWithImGuiProcess() = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const std::string& GetConverterID() const
  {
    return this->converter_id_;
  }

  inline const std::unordered_set<T_UINT32>& GetSubAssetUniqueIds() const
  {
    return this->sub_asset_unique_ids_;
  }

  inline bool IsDirty() const
  {
    return this->is_dirty_;
  }

  // =================================================================
  // Serialize Method
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(CEREAL_NVP(converter_id_));
    ar(CEREAL_NVP(sub_asset_unique_ids_));
    ar(CEREAL_NVP(is_dirty_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string converter_id_;
  std::unordered_set<T_UINT32> sub_asset_unique_ids_;
  bool is_dirty_;

};

CEREAL_CLASS_VERSION(ConverterSetting, 0);


