#pragma once

class TextureTestScene : public Scene
{
  // =================================================================
  // Methods from Scene
  // =================================================================
public:
  virtual void OnLoad() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

private:
  GameObject2D* obj_;
  Camera2D* camera_;

};