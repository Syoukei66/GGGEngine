#pragma once

#include <Scene/AssetViewer/AssetViewerBehavior.h>
#include <Engine/Component/Renderer/MeshRenderer.h>
#include <Scene/TestMesh/TestMesh.h>

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
  virtual void OnUpdate(const ActivityContext& activity_context, AssetConverterContext* context) override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<TestMesh> obj_;
};