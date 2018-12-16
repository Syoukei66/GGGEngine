#include "AssetViewerScene.h"
#include <Scene/AssetViewer/StaticMesh/StaticMeshViewerBehavior.h>
#include <Scene/AssetViewer/StaticModel/StaticModelViewerBehavior.h>
#include <Scene/AssetViewer/CharacterModel/CharacterModelViewerBehavior.h>
#include <Scene/AssetViewer/Texture/TextureViewerBehavior.h>

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
void AssetViewerScene::Run(const SharedRef<AssetEntity>& entity)
{
  SharedRef<AssetViewerBehavior> current_behavior = nullptr;
  for (const SharedRef<AssetViewerBehavior>& behavior : this->behaviors_)
  {
    if (behavior->IsTarget(entity->GetID()))
    {
      current_behavior = behavior;
      break;
    }
  }
  if (!current_behavior)
  {
    return;
  }
  current_behavior->SetEntity(entity);
  ViewerScene::Run(current_behavior);
}
