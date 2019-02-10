#pragma once

#include <Entity/AssetEntity.h>
#include <Engine/Scene/Scene.h>

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
public:
  void OnReload();

private:
  void ShowViewer(const SharedRef<AssetEntity>& entity);

  // =================================================================
  // Data Member
  // =================================================================
private:
  SharedRef<AssetEntity> selected_entity_;
  AssetConverterContext* context_;

  T_FLOAT elapsed_time_since_fetch_;

};