#include "AssetViewerScene.h"
#include <Scene/AssetViewer/StaticModel/StaticModelViewerBehavior.h>
#include <Scene/AssetViewer/CharacterModel/CharacterModelViewerBehavior.h>
#include <Scene/AssetViewer/Texture/TextureViewerBehavior.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(AssetViewerScene)
{
  //switch (entity->GetID())
  //{
  //  // Material
  //case AssetEntity::EntityID::ID_DEFAULT_MATERIAL:
  //  break;
  //case AssetEntity::EntityID::ID_MODEL_MATERIAL:
  //  break;
  //  // Texture
  //case AssetEntity::EntityID::ID_TEXTURE:
  //  break;
  //  // Text
  //case AssetEntity::EntityID::ID_CSV:
  //  break;
  //case AssetEntity::EntityID::ID_JSON:
  //  break;
  //  // Shader
  //case AssetEntity::EntityID::ID_SHADER:
  //  break;
  //  // Sound
  //case AssetEntity::EntityID::ID_SOUND:
  //  break;
  //  // Model
  //case AssetEntity::EntityID::ID_MODEL:
  //  break;
  //}
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
