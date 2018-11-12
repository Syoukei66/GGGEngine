#pragma once

class AssetEntity;

class AssetEntityView
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(AssetEntityView);

  // =================================================================
  // Methods
  // =================================================================
public:
  static void ShowEntity(AssetEntity* entity);

private:
  static void StartViewer(AssetEntity* entity);

};