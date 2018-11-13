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
  /*!
   * @brief AssetEntityの詳細情報を表示する
   * @return trueならビューワーを起動
   */
  static bool ShowEntity(AssetEntity* entity);

private:
  static void StartViewer(AssetEntity* entity);

};