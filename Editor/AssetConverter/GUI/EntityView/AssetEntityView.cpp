#include "AssetEntityView.h"
#include <Entity/AssetEntity.h>
#include <Entity/AssetInfo.h>

// =================================================================
// Methods
// =================================================================
bool AssetEntityView::ShowEntity(AssetEntity* entity)
{
  if (!entity)
  {
    return false;
  }
  ImGui::SetNextWindowPos(ImVec2(240.0f, 20.0f), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(640.0f, 480.0f), ImGuiSetCond_Once);
  ImGui::Begin("Entity Datas");

  const AssetInfo* info = entity->GetAssetInfo();
  const AssetMetaData* meta_data = info->GetMetaData();
  const URI& uri = info->GetURI();
  ImGui::Text((u8"ファイル名 : " + uri.GetPrefix()).c_str());
  ImGui::Text((u8"UniqueID : " + std::to_string(info->GetUniqueID())).c_str());
  ImGui::Text((u8"入力ディレクトリ : " + FileUtil::CreateSolutionPath(info->GetInputPath())).c_str());
  ImGui::Text((u8"出力ディレクトリ : " + FileUtil::CreateSolutionPath(info->GetOutputPath())).c_str());
  ImGui::Text((u8"タイムスタンプ : " + meta_data->GetTimeStamp()).c_str());

  bool open_viewer = ImGui::Button(u8"ビューワーを起動");

  ImGui::End();

  return open_viewer;
}

void AssetEntityView::StartViewer(AssetEntity* entity)
{

}
