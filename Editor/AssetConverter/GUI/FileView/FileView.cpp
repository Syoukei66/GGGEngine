#include "FileView.h"
#include <Converter/AssetConverterContext.h>

// =================================================================
// Methdos
// =================================================================
void FileView::Init(AssetConverterContext* context)
{
  FileView* self = &Self();
  self->root_ = AssetEntityFileNode::Create();
  context->VisitAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    self->root_->AddAssetEntity(entity);
  });
}

void FileView::Uninit()
{
  FileView* self = &Self();
  self->root_ = nullptr;
}

SharedRef<AssetEntity> FileView::SelectWithImGUI()
{
  FileView* self = &Self();

  ImGui::SetNextWindowPos(ImVec2(Application::GetMainActivity()->GetContext().GetScreenWidth() - 250.0f - 20.0f, 20.0f), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(250.0f, 600.0f), ImGuiSetCond_Once);

  ImGui::Begin("FileView");
  const SharedRef<AssetEntity>& entity = self->root_->SelectWithImGUI();
  ImGui::End();

  return entity;
}
