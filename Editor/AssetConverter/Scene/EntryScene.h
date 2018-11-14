#pragma once

#include <Scene/AssetViewer/AssetViewerScene.h>

class AssetEntity;

class EntryScene : public Scene
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(EntryScene);
  GG_CREATE_FUNC(EntryScene);

  // =================================================================
  // Methods from Scene
  // =================================================================
public:
  virtual void OnLoad() override;
  virtual void OnUnload() override;
  virtual void OnShow() override;
  virtual void OnHide() override;
  virtual void Update() override;

  // =================================================================
  // Methods
  // =================================================================
private:
  void ShowViewer(AssetEntity* entity);

  // =================================================================
  // Data Member
  // =================================================================
private:
  AssetEntity* selected_entity_;
  SharedRef<AssetViewerScene> viewer_scene_;

};