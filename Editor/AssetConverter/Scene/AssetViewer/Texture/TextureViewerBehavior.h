#pragma once

#include <Scene/AssetViewer/AssetViewerBehavior.h>
#include <Engine/Component/Renderer/MeshRenderer.h>

class TextureViewerBehavior : public AssetViewerBehavior
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(TextureViewerBehavior);
  GG_CREATE_FUNC(TextureViewerBehavior);

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
  // Methods from AssetViewerBehavior
  // =================================================================
public:
  void UpdateMesh();

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<GameObject3D> obj_;
  SharedRef<MeshRenderer> mesh_renderer_;

  T_INT32 mesh_mode_;
  std::vector<SharedRef<rcMesh>> meshes_;

};