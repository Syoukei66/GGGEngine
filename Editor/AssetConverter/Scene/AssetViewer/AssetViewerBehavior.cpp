#include "AssetViewerBehavior.h"
#include <Director.h>

// =================================================================
// Methods from IViewerBehavior
// =================================================================
void AssetViewerBehavior::Start(Scene* scene, AssetConverterContext* context)
{
  this->entity_->Load(context);
  this->OnStart(scene);
  this->OnLoad(this->entity_->GetMetaData()->GetUniqueID());
}

void AssetViewerBehavior::End()
{
  this->OnUnload();
  this->OnEnd();
}

bool AssetViewerBehavior::Update(const ActivityContext& activity_context, AssetConverterContext* context)
{
  ImGui::Begin(activity_context, u8"インポート設定", 10.0f, 0.0f, 0.35f, 0.25f, 0.65f);
  this->entity_->GetMetaData()->GetConverterSetting()->EditWithImGui();
  ImGui::End();

  bool reloaded = false;
  if (this->entity_->Load(context))
  {
    this->OnUnload();
    this->OnLoad(this->entity_->GetMetaData()->GetUniqueID());
    reloaded = true;
  }
  this->OnUpdate(activity_context);
  return reloaded;
}
