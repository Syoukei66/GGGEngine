#pragma once

class MeshTestScene : public Scene
{
  // =================================================================
  // Methods from Scene
  // =================================================================
  virtual void OnLoad() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

private:
  GameObject3D* obj_;
  Camera3D_LookAt* camera_;

};