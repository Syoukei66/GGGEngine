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
GG_CREATE_FUNC_IMPL_4(AssetViewerScene, const SharedRef<EntryScene>&, entry_scene, const SharedRef<AssetViewerBehavior>&, behavior, AssetConverterContext*, context, const SharedRef<AssetEntity>&, entity)
{
  behavior->SetEntity(entity);
  return ViewerScene::Init(entry_scene, behavior, context);
}

// =================================================================
// Methods from ViewerScene
// =================================================================
UniqueRef<AssetViewerScene> AssetViewerScene::Create(const SharedRef<EntryScene>& entry_scene, AssetConverterContext* context, const SharedRef<AssetEntity>& entity)
{
  SharedRef<AssetViewerBehavior> behavior = entity->GetConverter(context)->CreateViewerBehavior();
  if (!behavior)
  {
    return nullptr;
  }
  return Create(entry_scene, behavior, context, entity);
}
