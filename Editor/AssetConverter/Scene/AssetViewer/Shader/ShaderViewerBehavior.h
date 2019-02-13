#pragma once

#include <Scene/AssetViewer/AssetViewerBehavior.h>
#include <Engine/Component/Renderer/MeshRenderer.h>
#include <Scene/TestMesh/TestMesh.h>
#include <GUI/MaterialEditView/MaterialEditView.h>

class ShaderViewerBehavior : public AssetViewerBehavior
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(ShaderViewerBehavior);
  GG_CREATE_FUNC(ShaderViewerBehavior);

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
  std::vector<char> path_;
  MaterialEditView material_edit_view_;

};