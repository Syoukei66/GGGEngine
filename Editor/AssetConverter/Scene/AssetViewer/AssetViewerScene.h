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
  GG_CREATE_FUNC_4(AssetViewerScene, const SharedRef<EntryScene>&, entry_scene, const SharedRef<AssetViewerBehavior>&, behavior, AssetConverterContext*, context, const SharedRef<AssetEntity>&, entity);

  // =================================================================
  // Methods from ViewerScene
  // =================================================================
public:
  static UniqueRef<AssetViewerScene> Create(const SharedRef<EntryScene>& entry_scene, AssetConverterContext* context, const SharedRef<AssetEntity>& entity);

};