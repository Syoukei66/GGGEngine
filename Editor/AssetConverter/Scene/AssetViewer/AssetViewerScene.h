#pragma once

#include <Scene/ViewerScene.h>

#include "AssetViewerBehavior.h"

class AssetConverterContext;
class AssetEntity;

//ViewerScene�ł̃z�b�g�����[�h�̎���
//(�^�C���X�^���v���Ď����A�X�V������������Director�o�R�ł��̃A�Z�b�g���ăC���|�[�g���AAssetEntity��CommitChanges�����s����)

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