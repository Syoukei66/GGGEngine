#pragma once

#include <Cereal/cereal.hpp>
#include "URI.h"
#include <Engine/GameObject/Transform/Transform.h>

class AssetConverterContext;

/*!
 * Converterの設定。
 */
class ConverterSetting
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief デフォルトコンストラクタ。シリアライズ用
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
   * @brief ImGUIを使ってデータを編集する
   */
  inline void EditWithImGui(AssetConverterContext* context)
  {
    this->is_dirty_ |= this->EditWithImGuiProcess(context);
  }

  /*!
   * @brief 自身を使用してデータを読み込んだらダーティフラグを削除
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
   * @brief ImGUIを使ってデータを編集する処理を記述する。
   * @return データに変更があった場合true
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


