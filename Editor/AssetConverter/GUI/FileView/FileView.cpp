#include "FileView.h"
#include <Converter/AssetConverterContext.h>
#include <Util/ImGuiUtil.h>

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

SharedRef<AssetEntity> FileView::SelectWithImGUI(const ActivityContext& context)
{
  FileView* self = &Self();

  ImGui::Begin(context, u8"FileView", 10.0f, 0.75f, 0.0f, 0.25f, 1.0f);
  const SharedRef<AssetEntity>& entity = self->root_->SelectWithImGUI();
  ImGui::End();

  return entity;
}
