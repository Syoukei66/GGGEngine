#pragma once

#include <Scene/AssetViewer/AssetViewerBehavior.h>
#include <Engine/Component/Renderer/MeshRenderer.h>

class StaticMeshViewerBehavior : public AssetViewerBehavior
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(StaticMeshViewerBehavior);
  GG_CREATE_FUNC(StaticMeshViewerBehavior);

  // =================================================================
  // Methods from AssetViewerBehavior
  // =================================================================
public:
  virtual void OnStart(Scene* scene) override;
  virtual void OnEnd() override;
  virtual void OnLoad(T_UINT32 unique_id) override;
  virtual void OnUnload() override;
  virtual SharedRef<GameObject> GetTargetObject() const override
  {
    return this->obj_;
  }
  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<GameObject> obj_;
  SharedRef<MeshRenderer> mesh_renderer_;
};