#pragma once

#include <Engine/GameObject/GameObject3D.h>

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
  virtual void Start(Scene* scene) = 0;
  virtual void End() = 0;
  virtual void Update() = 0;
  virtual bool IsTarget(T_UINT32 id) = 0;
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
  GG_CREATE_FUNC(ViewerScene);

  // =================================================================
  // Methods from Scene
  // =================================================================
public:
  virtual void OnLoad() override;
  virtual void OnUnload() override;
  virtual void OnShow() override;
  virtual void OnHide() override;
  virtual void Update() override;

  // =================================================================
  // Methods
  // =================================================================
public:
  void Run(const SharedRef<IViewerBehavior>& behavior);

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<IViewerBehavior> current_behavior_;
  SharedRef<GameObject3D> camera_2d_;
  SharedRef<GameObject3D> camera_3d_;
  T_FLOAT camera_move_x_;
  T_FLOAT camera_move_y_;

  T_INT32 camera_state_;
  T_FLOAT move_speed_;
  T_FLOAT move_speed_weight_;
  TColor bg_color_;
  
};