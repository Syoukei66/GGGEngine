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

void AssetViewerBehavior::Update(AssetConverterContext* context)
{
  ImGui::SetNextWindowPos(ImVec2(20, 250), ImGuiCond_Once);
  ImGui::SetNextWindowSize(ImVec2(350, 450), ImGuiCond_Once);
  ImGui::Begin(u8"インポート設定");
  this->entity_->GetMetaData()->GetConverterSetting()->EditWithImGui();
  ImGui::End();

  if (this->entity_->Load(context))
  {
    this->OnUnload();
    this->OnLoad(this->entity_->GetMetaData()->GetUniqueID());
  }
  this->OnUpdate();
}
