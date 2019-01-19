#include "AssetViewerBehavior.h"
#include <Director.h>

// =================================================================
// Methods from IViewerBehavior
// =================================================================
void AssetViewerBehavior::Start(Scene* scene)
{
  this->OnStart(scene);
  this->OnLoad(this->entity_->GetMetaData()->GetUniqueID());
}

void AssetViewerBehavior::End()
{
  this->OnUnload();
  this->OnEnd();
}

void AssetViewerBehavior::Update(AssetConverterContext* context)
{
  if (this->entity_->Load(context))
  {
    this->OnUnload();
    this->OnLoad(this->entity_->GetMetaData()->GetUniqueID());
  }
  this->OnUpdate();
}
