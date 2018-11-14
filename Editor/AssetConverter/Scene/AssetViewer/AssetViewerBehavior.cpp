#include "AssetViewerBehavior.h"
#include <Director.h>

// =================================================================
// Methods from IViewerBehavior
// =================================================================
void AssetViewerBehavior::Start(Scene* scene)
{
  this->OnStart(scene);
  this->OnLoad(this->entity_->GetAssetInfo()->GetUniqueID());
}

void AssetViewerBehavior::End()
{
  this->OnUnload();
  this->OnEnd();
}

void AssetViewerBehavior::Update()
{
  std::set<SharedRef<AssetEntity>> changed_entities_ = std::set<SharedRef<AssetEntity>>();
  this->entity_->CheckChanged(&changed_entities_);
  bool entity_changed = changed_entities_.size() > 0;
  const T_UINT32 unique_id = this->entity_->GetAssetInfo()->GetUniqueID();
  for (const SharedRef<AssetEntity>& entity : changed_entities_)
  {
    AssetConverterDirector::GetContext()->ImportImmediately(entity->GetAssetInfo()->GetURI(), true);
  }
  if (entity_changed)
  {
    this->entity_ = AssetConverterDirector::GetContext()->GetEntity(unique_id);
    this->entity_->CommitChanges();
    this->OnUnload();
    this->OnLoad(this->entity_->GetAssetInfo()->GetUniqueID());
  }
  this->OnUpdate();
}
