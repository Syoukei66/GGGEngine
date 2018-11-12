#include "FileView.h"
#include <Director.h>

// =================================================================
// Methdos
// =================================================================
void FileView::Init()
{
  FileView* self = &Self();
  self->root_ = AssetEntityFileNode::Create();
  AssetConverterContext* context = AssetConverterDirector::GetContext();
  context->VisitAllEntity([&](AssetEntity* entity)
  {
    self->root_->AddAssetEntity(entity);
  });
}

void FileView::Uninit()
{
  FileView* self = &Self();
  self->root_ = nullptr;
}

AssetEntity* FileView::SelectWithImGUI()
{
  FileView* self = &Self();

  ImGui::SetNextWindowPos(ImVec2(Application::GetMainActivity()->GetScreenWidth() - 250.0f - 20.0f, 20.0f), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(250.0f, 600.0f), ImGuiSetCond_Once);

  ImGui::Begin("FileView");
  AssetEntity* entity = self->root_->SelectWithImGUI();
  ImGui::End();

  return entity;
}
