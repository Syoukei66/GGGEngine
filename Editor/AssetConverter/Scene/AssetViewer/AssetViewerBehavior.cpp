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

void AssetViewerBehavior::Update()
{
  std::set<SharedRef<AssetEntity>> changed_entities_ = std::set<SharedRef<AssetEntity>>();

  // アセットに変更があるか検出
  this->entity_->CheckAssetChanged(&changed_entities_);
  if (changed_entities_.size() > 0)
  {
    // 変更があったアセットをインポートし直す
    for (const SharedRef<AssetEntity>& entity : changed_entities_)
    {
      AssetConverterDirector::GetContext()->ImportImmediately(entity->GetMetaData()->GetURI(), true);
    }
    // サブアセットの変更を検出
    this->entity_->CheckSubAssetChanged();

    // AssetEntityをリフレッシュし、シーンのリロードを行う
    this->entity_ = AssetConverterDirector::GetContext()->GetEntity(this->entity_->GetMetaData()->GetUniqueID());
    this->entity_->CommitChanges();
    this->OnUnload();
    this->OnLoad(this->entity_->GetMetaData()->GetUniqueID());
  }
  this->OnUpdate();
}
