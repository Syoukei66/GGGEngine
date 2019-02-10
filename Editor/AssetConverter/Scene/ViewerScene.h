#pragma once

#include <Engine/GameObject/GameObject.h>
#include <Engine/Scene/Scene.h>
#include <Scene/EntryScene.h>

class AssetConverterContext;

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
  virtual bool Update(const ActivityContext& activity_context, AssetConverterContext* context) = 0;
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
  GG_INIT_FUNC_3(ViewerScene, const SharedRef<EntryScene>&, const SharedRef<IViewerBehavior>&, AssetConverterContext*);

  // =================================================================
  // Methods from Scene
  // =================================================================
public:
  virtual void OnLoad(const ActivityContext& context) override;
  virtual void OnUnload(const ActivityContext& context) override;
  virtual void OnShow(const ActivityContext& context) override;
  virtual void OnHide(const ActivityContext& context) override;
  virtual void Update(const ActivityContext& context) override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<EntryScene> entry_scene_;

  AssetConverterContext* current_context_;
  SharedRef<IViewerBehavior> current_behavior_;
  SharedRef<GameObject> camera_;
  SharedRef<GameObject> camera_target_;
  T_FLOAT camera_move_x_;
  T_FLOAT camera_move_y_;

  T_INT32 camera_state_;
  T_FLOAT move_speed_;
  T_FLOAT move_speed_weight_;
  TColor bg_color_;
  
};