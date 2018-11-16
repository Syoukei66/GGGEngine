#pragma once

#include <Scene/AssetViewer/AssetViewerBehavior.h>

class MeshRenderer;

class ModelViewerBehavior : public AssetViewerBehavior
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(ModelViewerBehavior);
  GG_CREATE_FUNC(ModelViewerBehavior);
  GG_DESTRUCT_FUNC(ModelViewerBehavior);

  // =================================================================
  // Methods from AssetViewerBehavior
  // =================================================================
public:
  virtual void OnStart(Scene* scene) override;
  virtual void OnEnd() override;
  virtual void OnLoad(T_UINT32 unique_id) override;
  virtual void OnUnload() override;
  virtual bool IsTarget(T_UINT32 id) override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  Scene* scene_;
  GameObject3D* root_;
};