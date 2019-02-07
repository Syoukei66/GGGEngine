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
  virtual void OnUpdate() override;

  // =================================================================
  // Methods
  // =================================================================
private:
  template <typename Type_>
  void SetMaterialProperty(const std::string& name, T_UINT8 count, T_UINT32 offset, size_t size, const MaterialData* data)
  {
    for (T_UINT8 i = 0; i < count; ++i)
    {
      this->material_->GetProperty<Type_>(name, i) = *(Type_*)&data->data_[offset + size * i];
    }
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<TestMesh> obj_;
  SharedRef<rcMaterial> material_;
};