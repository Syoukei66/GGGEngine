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
  GG_CREATE_FUNC_3(AssetViewerScene, const SharedRef<AssetViewerBehavior>&, AssetConverterContext*, const SharedRef<AssetEntity>&);
  
public:
  static UniqueRef<AssetViewerScene> Create(AssetConverterContext*, const SharedRef<AssetEntity>&);

};