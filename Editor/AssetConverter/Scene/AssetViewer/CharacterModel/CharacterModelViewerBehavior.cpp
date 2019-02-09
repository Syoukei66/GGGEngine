#include "CharacterModelViewerBehavior.h"
#include <Engine/GameObject/GameObjectFactory.h>

#include <GUI/HierarchyView/HierarchyView.h>

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
  HierarchyView::StartViewer(this->scene_);
}

void CharacterModelViewerBehavior::OnUnload()
{
  HierarchyView::EndViewer();
  this->root_->RemoveSelf();
  this->root_ = nullptr;
}

void CharacterModelViewerBehavior::OnUpdate(const ActivityContext& activity_context)
{
  HierarchyView::EditWithImGUI(activity_context);
}
