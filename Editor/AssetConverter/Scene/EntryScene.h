#pragma once

#include <Scene/AssetViewer/AssetViewerScene.h>

class AssetEntity;
class AssetConverterContext;

class EntryScene : public Scene
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(EntryScene);
  GG_CREATE_FUNC_1(EntryScene, AssetConverterContext*);

  // =================================================================
  // Methods from Scene
  // =================================================================
public:
  virtual void OnLoad() override;
  virtual void OnUnload() override;
  virtual void OnShow() override;
  virtual void OnHide() override;
  virtual void Update(const ActivityContext& context) override;

  // =================================================================
  // Methods
  // =================================================================
private:
  void ShowViewer(const SharedRef<AssetEntity>& entity);

  // =================================================================
  // Data Member
  // =================================================================
private:
  SharedRef<AssetEntity> selected_entity_;
  SharedRef<AssetViewerScene> viewer_scene_;
  AssetConverterContext* context_;

};