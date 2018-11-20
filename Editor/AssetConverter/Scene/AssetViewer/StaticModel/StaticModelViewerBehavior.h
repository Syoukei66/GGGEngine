#pragma once

#include <Scene/AssetViewer/AssetViewerBehavior.h>

class MeshRenderer;

class StaticModelViewerBehavior : public AssetViewerBehavior
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(StaticModelViewerBehavior);
  GG_CREATE_FUNC(StaticModelViewerBehavior);
  GG_DESTRUCT_FUNC(StaticModelViewerBehavior);

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
  SharedRef<GameObject3D> root_;

};