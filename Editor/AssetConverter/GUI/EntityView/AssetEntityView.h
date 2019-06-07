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
  static bool ShowEntity(const ActivityContext& context, const SharedRef<AssetEntity>& entity);

private:
  static void StartViewer(const SharedRef<AssetEntity>& entity);

};