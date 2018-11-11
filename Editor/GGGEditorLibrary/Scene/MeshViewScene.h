#pragma once

class MeshViewScene : public Scene
{
public:
  virtual void OnLoad() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;
};