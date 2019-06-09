#include "StaticModelViewerBehavior.h"
#include <Engine/GameObject/GameObjectFactory.h>

// =================================================================
// GGG Statement
// =================================================================
GG_CREATE_FUNC_IMPL(StaticModelViewerBehavior)
{
  this->root_ = GameObject::Create();
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
  this->scene_->AddChild(this->root_);
}

void StaticModelViewerBehavior::OnEnd()
{
  this->root_->RemoveSelf();
}

void StaticModelViewerBehavior::OnLoad(T_UINT32 unique_id, AssetConverterContext* context)
{
  const SharedRef<rcStaticModel>& model = AssetManager::Load<rcStaticModel>(unique_id);
  this->model_ = GameObjectFactory::Create(model);
  this->root_->AddChild(this->model_);
}

void StaticModelViewerBehavior::OnUnload()
{
  this->model_->RemoveSelf();
  this->model_ = nullptr;
}