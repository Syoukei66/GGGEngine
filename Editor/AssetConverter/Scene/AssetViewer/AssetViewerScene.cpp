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
GG_INIT_FUNC_IMPL(AssetViewerScene)
{
  this->behaviors_.push_back(StaticMeshViewerBehavior::Create());
  this->behaviors_.push_back(StaticModelViewerBehavior::Create());
  this->behaviors_.push_back(CharacterModelViewerBehavior::Create());
  this->behaviors_.push_back(TextureViewerBehavior::Create());
  return ViewerScene::Init();
}
// =================================================================
// Methods
// =================================================================
void AssetViewerScene::Run(const SharedRef<GameActivity>& activity, const SharedRef<AssetEntity>& entity, AssetConverterContext* context)
{
  SharedRef<AssetViewerBehavior> behavior = entity->GetConverter(context)->GetViewerBehavior();
  if (!behavior)
  {
    return;
  }
  behavior->SetEntity(entity);
  ViewerScene::Run(activity, behavior, context);
}
