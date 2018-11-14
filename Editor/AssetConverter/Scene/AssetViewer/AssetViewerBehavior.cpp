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
  std::set<std::string> changed_paths_ = std::set<std::string>();
  this->entity_->CheckChanged(&changed_paths_);
  bool entity_changed = changed_paths_.size() > 0;
  const T_UINT32 unique_id = this->entity_->GetAssetInfo()->GetUniqueID();
  for (const URI& uri : changed_paths_)
  {
    AssetConverterDirector::GetContext()->ImportImmediately(uri, true);
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
