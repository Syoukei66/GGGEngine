#pragma once

#include <Scene/ViewerScene.h>

#include "AssetViewerBehavior.h"

class AssetEntity;

//ViewerSceneでのホットリロードの実現
//(タイムスタンプを監視し、更新があった時にDirector経由でそのアセットを再インポートし、AssetEntityのCommitChangesを実行する)

class AssetViewerScene : public ViewerScene
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(AssetViewerScene);
  GG_CREATE_FUNC(AssetViewerScene);

  // =================================================================
  // Methods
  // =================================================================
public:
  void Run(const SharedRef<AssetEntity>& entity);

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::vector<SharedRef<AssetViewerBehavior>> behaviors_;

};