#pragma once

#include <Scene/AssetViewer/AssetViewerBehavior.h>
#include <Engine/Component/Renderer/MeshRenderer.h>

class MaterialViewerBehavior : public AssetViewerBehavior
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(MaterialViewerBehavior);
  GG_CREATE_FUNC(MaterialViewerBehavior);

  // =================================================================
  // Methods from AssetViewerBehavior
  // =================================================================
public:
  virtual void OnStart(Scene* scene) override;
  virtual void OnEnd() override;
  virtual void OnLoad(T_UINT32 unique_id) override;
  virtual void OnUnload() override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<GameObject3D> obj_;
  SharedRef<MeshRenderer> mesh_renderer_;

};