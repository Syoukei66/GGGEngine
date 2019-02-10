#pragma once

#include <Cereal/cereal.hpp>
#include "URI.h"
#include <Engine/GameObject/Transform/Transform.h>

class AssetConverterContext;

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
    , camera_position_(TVec3f(0.0f, 0.0f, -10.0f))
    , camera_rotation_()
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
  inline void EditWithImGui(AssetConverterContext* context)
  {
    this->is_dirty_ |= this->EditWithImGuiProcess(context);
  }

  /*!
   * @brief ���g���g�p���ăf�[�^��ǂݍ��񂾂�_�[�e�B�t���O���폜
   */
  inline void ClearDirty()
  {
    this->is_dirty_ = false;
  }

  inline void SetCameraState(Transform* transform)
  {
    this->camera_position_ = transform->GetPosition();
    this->camera_rotation_ = transform->GetQuaternion();
  }

  inline void GetCameraState(Transform* transform) const
  {
    transform->SetPosition(this->camera_position_);
    transform->SetQuaternion(this->camera_rotation_);
  }

protected:
  /*!
   * @brief ImGUI���g���ăf�[�^��ҏW���鏈�����L�q����B
   * @return �f�[�^�ɕύX���������ꍇtrue
   */
  virtual bool EditWithImGuiProcess(AssetConverterContext* context) = 0;

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
    ar(CEREAL_NVP(camera_position_));
    ar(CEREAL_NVP(camera_rotation_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string converter_id_;
  std::unordered_set<T_UINT32> sub_asset_unique_ids_;
  bool is_dirty_;
  TVec3f camera_position_;
  Quaternion camera_rotation_;

};

CEREAL_CLASS_VERSION(ConverterSetting, 0);


