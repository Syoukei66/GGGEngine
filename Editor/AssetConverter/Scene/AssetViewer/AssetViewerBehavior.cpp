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

  // �A�Z�b�g�ɕύX�����邩���o
  this->entity_->CheckAssetChanged(&changed_entities_);
  if (changed_entities_.size() > 0)
  {
    // �ύX���������A�Z�b�g���C���|�[�g������
    for (const SharedRef<AssetEntity>& entity : changed_entities_)
    {
      AssetConverterDirector::GetContext()->ImportImmediately(entity->GetMetaData()->GetURI(), true);
    }
    // �T�u�A�Z�b�g�̕ύX�����o
    this->entity_->CheckSubAssetChanged();

    // AssetEntity�����t���b�V�����A�V�[���̃����[�h���s��
    this->entity_ = AssetConverterDirector::GetContext()->GetEntity(this->entity_->GetMetaData()->GetUniqueID());
    this->entity_->CommitChanges();
    this->OnUnload();
    this->OnLoad(this->entity_->GetMetaData()->GetUniqueID());
  }
  this->OnUpdate();
}
