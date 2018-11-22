#pragma once

class TextureViewScene : public Scene
{
  // =================================================================
  // Methods from Scene
  // =================================================================
public:
  virtual void OnLoad() override;
  virtual void OnUnload() override;
  virtual void OnShow() override;
  virtual void OnHide() override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  SharedRef<GameObject2D> obj_;
  SharedRef<GameObject2D> camera_;

};