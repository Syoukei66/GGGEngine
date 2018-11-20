#include "ModelViewerBehavior.h"
#include <Engine/GameObject/Transform/Transform3D.h>
#include <Engine/GameObject/GameObjectFactory.h>
#include <Engine/Component/Renderer/MeshRenderer.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(ModelViewerBehavior)
{
  return true;
}

GG_DESTRUCT_FUNC_IMPL(ModelViewerBehavior)
{
  return true;
}

// =================================================================
// Methods from AssetViewerBehavior
// =================================================================
void ModelViewerBehavior::OnStart(Scene* scene)
{
  this->scene_ = scene;
}

void ModelViewerBehavior::OnEnd()
{
}

void ModelViewerBehavior::OnLoad(T_UINT32 unique_id)
{
  const SharedRef<rcStaticModel>& model = AssetManager::Load<rcStaticModel>(unique_id);
  this->root_ = GameObjectFactory::Create(model);
  this->scene_->AddChild(this->root_);
}

void ModelViewerBehavior::OnUnload()
{
  this->root_->RemoveSelf();
  delete this->root_;
}

bool ModelViewerBehavior::IsTarget(T_UINT32 id)
{
  return id == AssetEntity::EntityID::ID_STATIC_MODEL;
}
