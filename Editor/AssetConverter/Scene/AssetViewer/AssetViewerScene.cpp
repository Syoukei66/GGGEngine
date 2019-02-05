#include "AssetViewerScene.h"
#include <Scene/AssetViewer/StaticMesh/StaticMeshViewerBehavior.h>
#include <Scene/AssetViewer/StaticModel/StaticModelViewerBehavior.h>
#include <Scene/AssetViewer/CharacterModel/CharacterModelViewerBehavior.h>
#include <Scene/AssetViewer/Texture/TextureViewerBehavior.h>

#include <Entity/AssetEntity.h>
#include <Converter/AssetConverter.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_3(AssetViewerScene, const SharedRef<AssetViewerBehavior>& behavior, AssetConverterContext* context, const SharedRef<AssetEntity>& entity)
{
  behavior->SetEntity(entity);
  return ViewerScene::Init(behavior, context);
}

UniqueRef<AssetViewerScene> AssetViewerScene::Create(AssetConverterContext* context, const SharedRef<AssetEntity>& entity)
{
  SharedRef<AssetViewerBehavior> behavior = entity->GetConverter(context)->CreateViewerBehavior();
  if (!behavior)
  {
    return nullptr;
  }
  return Create(behavior, context, entity);
}
