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
  virtual void Update() {};
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
  void Run(IViewerBehavior* behavior);

  // =================================================================
  // Data Members
  // =================================================================
private:
  IViewerBehavior* behavior_;
  Camera3D_LookAt* camera_2d_;
  Camera3D_LookAt* camera_3d_;
  CameraState state_;
  T_FLOAT look_at_rot_x_;
  T_FLOAT look_at_rot_y_;

};