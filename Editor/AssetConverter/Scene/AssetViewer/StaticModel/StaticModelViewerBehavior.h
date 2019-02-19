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
  virtual void OnLoad(T_UINT32 unique_id, AssetConverterContext* context) override;
  virtual void OnUnload() override;
  virtual SharedRef<GameObject> GetTargetObject() const override
  {
    return this->root_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  Scene* scene_;
  SharedRef<GameObject> root_;
  SharedRef<GameObject> model_;

};