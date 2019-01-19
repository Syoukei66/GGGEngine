#pragma once

#include <Scene/AssetViewer/AssetViewerBehavior.h>

class CharacterModelViewerBehavior : public AssetViewerBehavior
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(CharacterModelViewerBehavior);
  GG_CREATE_FUNC(CharacterModelViewerBehavior);
  GG_DESTRUCT_FUNC(CharacterModelViewerBehavior);

  // =================================================================
  // Methods from AssetViewerBehavior
  // =================================================================
public:
  virtual void OnStart(Scene* scene) override;
  virtual void OnEnd() override;
  virtual void OnLoad(T_UINT32 unique_id) override;
  virtual void OnUnload() override;

  virtual void OnUpdate() override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  Scene* scene_;
  SharedRef<GameObject3D> root_;

};