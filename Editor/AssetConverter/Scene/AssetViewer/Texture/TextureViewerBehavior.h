#pragma once

#include <Scene/AssetViewer/AssetViewerBehavior.h>
#include <Engine/Component/Renderer/MeshRenderer.h>
#include <Scene/TestMesh/TestMesh.h>

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
  virtual void OnLoad(T_UINT32 unique_id, AssetConverterContext* context) override;
  virtual void OnUnload() override;
  virtual void OnUpdate(const ActivityContext& activity_context, AssetConverterContext* context) override;
  virtual SharedRef<GameObject> GetTargetObject() const override
  {
    return this->obj_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<TestMesh> obj_;

};