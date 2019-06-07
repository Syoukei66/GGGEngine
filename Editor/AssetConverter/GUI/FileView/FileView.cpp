#include "FileView.h"
#include <Converter/AssetConverter.h>
#include <Converter/AssetConverterContext.h>
#include <Util/ImGuiUtil.h>
#include <Windows.h>

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

SharedRef<AssetEntity> FileView::SelectWithImGUI(const ActivityContext& activity_context, AssetConverterContext* context)
{
  FileView* self = &Self();

  const std::map<std::string, AssetConverter*>& newable_converter_map = context->GetNewableAssetConverters();

  ImGui::Begin(activity_context, u8"FileView", 10.0f, 0.75f, 0.0f, 0.25f, 1.0f, ImGuiWindowFlags_MenuBar);

  if (ImGui::BeginMenuBar())
  {
    if (ImGui::BeginMenu(u8"ファイル"))
    {
      if (ImGui::BeginMenu(u8"新規アセット作成"))
      {
        for (const auto& pair : newable_converter_map)
        {
          if (ImGui::MenuItem(pair.first.c_str()))
          {
            char szFullPath[512] = { 0 };
            char* szFilePart;
            GetFullPathName(FileUtil::GetInputPath().c_str(), 512, szFullPath, &szFilePart);

            TCHAR szFile[512] = { 0 };
            OPENFILENAME ofn = OPENFILENAME();
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = (HWND)activity_context.GetActivityID();
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = "All\0*.*\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = szFullPath;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
            if (GetSaveFileNameA(&ofn))
            {
              pair.second->CreateNewInstance(std::string(szFile));
            }
          }
        }
        ImGui::EndMenu();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

  const SharedRef<AssetEntity>& entity = self->root_->SelectWithImGUI();
  ImGui::End();

  return entity;
}
