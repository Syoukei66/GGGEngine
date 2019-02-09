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
   * @brief AssetEntity�̏ڍ׏���\������
   * @return true�Ȃ�r���[���[���N��
   */
  static bool ShowEntity(const ActivityContext& context, const SharedRef<AssetEntity>& entity);

private:
  static void StartViewer(const SharedRef<AssetEntity>& entity);

};