#include "AssetViewerBehavior.h"
#include <Director.h>
#include <Util/ImGuiUtil.h>

// =================================================================
// Methods from IViewerBehavior
// =================================================================
void AssetViewerBehavior::Start(Scene* scene, AssetConverterContext* context)
{
  this->entity_->Load(context);
  this->OnStart(scene);
  this->OnLoad(this->entity_->GetMetaData()->GetUniqueID(), context);
}

void AssetViewerBehavior::End()
{
  this->OnUnload();
  this->OnEnd();
}

bool AssetViewerBehavior::Update(const ActivityContext& activity_context, AssetConverterContext* context)
{
  ImGui::Begin(activity_context, u8"インポート設定", 10.0f, 0.0f, 0.35f, 0.25f, 0.65f);
  this->entity_->GetMetaData()->GetConverterSetting()->EditWithImGui(context);
  ImGui::End();

  bool reloaded = this->entity_->Load(context);
  for (const auto& entity : this->use_entities_)
  {
    reloaded |= entity->Load(context);
  }
  if (reloaded)
  {
    this->OnUnload();
    this->OnLoad(this->entity_->GetMetaData()->GetUniqueID(), context);
  }
  this->OnUpdate(activity_context, context);
  return reloaded;
}
