#include "AssetEntityView.h"
#include <Entity/AssetEntity.h>
#include <Entity/AssetMetaData.h>

// =================================================================
// Methods
// =================================================================
bool AssetEntityView::ShowEntity(const SharedRef<AssetEntity>& entity)
{
  if (!entity)
  {
    return false;
  }
  ImGui::SetNextWindowPos(ImVec2(240.0f, 20.0f), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(640.0f, 480.0f), ImGuiSetCond_Once);
  ImGui::Begin("Entity Datas");

  const AssetMetaData* meta = entity->GetMetaData();
  const URI& uri = meta->GetURI();
  ImGui::Text((u8"ファイル名 : " + uri.GetPrefix()).c_str());
  ImGui::Text((u8"UniqueID : " + std::to_string(meta->GetUniqueID())).c_str());
  ImGui::Text((u8"入力ディレクトリ : " + FileUtil::CreateSolutionPath(meta->GetInputPath())).c_str());
  ImGui::Text((u8"出力ディレクトリ : " + FileUtil::CreateSolutionPath(meta->GetOutputPath())).c_str());
  ImGui::Text((u8"タイムスタンプ : " + meta->GetTimeStamp()).c_str());

  bool open_viewer = ImGui::Button(u8"ビューワーを起動");

  ImGui::End();

  return open_viewer;
}

void AssetEntityView::StartViewer(const SharedRef<AssetEntity>& entity)
{

}
