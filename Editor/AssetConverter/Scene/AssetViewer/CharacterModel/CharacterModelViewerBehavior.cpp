#include "CharacterModelViewerBehavior.h"
#include <Engine/GameObject/GameObjectFactory.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(CharacterModelViewerBehavior)
{
  return true;
}

GG_DESTRUCT_FUNC_IMPL(CharacterModelViewerBehavior)
{
  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void CharacterModelViewerBehavior::OnStart(Scene* scene)
{
  this->scene_ = scene;
}

void CharacterModelViewerBehavior::OnEnd()
{
}

void CharacterModelViewerBehavior::OnLoad(T_UINT32 unique_id)
{
  const SharedRef<rcCharacterModel>& model = AssetManager::Load<rcCharacterModel>(unique_id);
  this->root_ = GameObjectFactory::Create(model);
  this->scene_->AddChild(this->root_);
}

void CharacterModelViewerBehavior::OnUnload()
{
  this->root_->RemoveSelf();
  this->root_ = nullptr;
}

bool CharacterModelViewerBehavior::IsTarget(T_UINT32 id)
{
  return id == AssetEntity::EntityID::ID_CHARACTER_MODEL;
}
