#pragma once

#include <Scene/ViewerScene.h>

#include "AssetViewerBehavior.h"

class AssetConverterContext;
class AssetEntity;

//ViewerSceneでのホットリロードの実現
//(タイムスタンプを監視し、更新があった時にDirector経由でそのアセットを再インポートし、AssetEntityのCommitChangesを実行する)

class AssetViewerScene : public ViewerScene
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(AssetViewerScene);
  GG_CREATE_FUNC_3(AssetViewerScene, const SharedRef<AssetViewerBehavior>&, AssetConverterContext*, const SharedRef<AssetEntity>&);
  
public:
  static UniqueRef<AssetViewerScene> Create(AssetConverterContext*, const SharedRef<AssetEntity>&);

};