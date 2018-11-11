#pragma once

class TextureViewScene : public Scene
{
  // =================================================================
  // Methods from Scene
  // =================================================================
public:
  virtual void OnLoad() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject2D* obj_;
  Camera2D* camera_3d_;

};