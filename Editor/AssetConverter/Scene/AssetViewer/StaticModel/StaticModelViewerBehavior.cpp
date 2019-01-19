#include "StaticModelViewerBehavior.h"
#include <Engine/GameObject/GameObjectFactory.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(StaticModelViewerBehavior)
{
  return true;
}

GG_DESTRUCT_FUNC_IMPL(StaticModelViewerBehavior)
{
  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void StaticModelViewerBehavior::OnStart(Scene* scene)
{
  this->scene_ = scene;
}

void StaticModelViewerBehavior::OnEnd()
{
}

void StaticModelViewerBehavior::OnLoad(T_UINT32 unique_id)
{
  const SharedRef<rcStaticModel>& model = AssetManager::Load<rcStaticModel>(unique_id);
  this->root_ = GameObjectFactory::Create(model);
  this->scene_->AddChild(this->root_);
}

void StaticModelViewerBehavior::OnUnload()
{
  this->root_->RemoveSelf();
  this->root_ = nullptr;
}