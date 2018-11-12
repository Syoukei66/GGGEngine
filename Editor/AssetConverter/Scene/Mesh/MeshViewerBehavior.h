#pragma once

#include <Scene/AssetViewerBehavior.h>

class MeshViewerBehavior : public AssetViewerBehavior<MeshData>
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(MeshViewerBehavior);
  GG_CREATE_FUNC(MeshViewerBehavior);
  GG_DESTRUCT_FUNC(MeshViewerBehavior);

  // =================================================================
  // Methods from AssetViewerBehavior
  // =================================================================
public:
  virtual void OnStart(const MeshData* data, Scene* scene) override;
  virtual void OnEnd() override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  GameObject3D* obj_;

};