#pragma once

#include <Engine/GameObject/GameObject3D.h>
#include <Engine/Scene/Scene.h>

class AssetConverterContext;
class AssetEntity;

/*!
 * @brief Viewerが表示するオブジェクトや
 * アップデート時のイベントを定義するインターフェース
 */
class IViewerBehavior : public GGObject
{
  // =================================================================
  // Methods from Scene
  // =================================================================
public:
  virtual void Start(Scene* scene, AssetConverterContext* context) = 0;
  virtual void End() = 0;
  virtual void Update(AssetConverterContext* context) = 0;
  virtual SharedRef<AssetEntity> GetEntity() const = 0;
};

class ViewerScene : public Scene
{
public:
  enum CameraState
  {
    CAMERA_3D,
    CAMERA_3D_ANCHOR_CENTER,
    CAMERA_2D,

    CAMERA_STATE_MAX,
  };

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(ViewerScene);
  GG_INIT_FUNC_2(ViewerScene, const SharedRef<IViewerBehavior>&, AssetConverterContext*);

  // =================================================================
  // Methods from Scene
  // =================================================================
public:
  virtual void OnLoad() override;
  virtual void OnUnload() override;
  virtual void OnShow() override;
  virtual void OnHide() override;
  virtual void Update(const ActivityContext& context) override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetConverterContext* current_context_;
  SharedRef<IViewerBehavior> current_behavior_;
  SharedRef<GameObject3D> camera_3d_;
  SharedRef<GameObject3D> camera_target_;
  T_FLOAT camera_move_x_;
  T_FLOAT camera_move_y_;

  T_INT32 camera_state_;
  T_FLOAT move_speed_;
  T_FLOAT move_speed_weight_;
  TColor bg_color_;
  
};