#pragma once

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

class Camera3D_LookAt;

class ViewerScene : public Scene
{
  enum CameraState
  {
    CAMERA_2D,
    CAMERA_3D,
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
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;
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
  Camera3D_LookAt* camera_2d_;
  Camera3D_LookAt* camera_3d_;
  CameraState state_;
  T_FLOAT look_at_rot_x_;
  T_FLOAT look_at_rot_y_;

  T_FLOAT move_speed_;

};