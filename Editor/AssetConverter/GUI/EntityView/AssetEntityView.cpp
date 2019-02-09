#include "AssetEntityView.h"
#include <Entity/AssetEntity.h>
#include <Entity/AssetMetaData.h>

// =================================================================
// Methods
// =================================================================
bool AssetEntityView::ShowEntity(const ActivityContext& context, const SharedRef<AssetEntity>& entity)
{
  if (!entity)
  {
    return false;
  }
  ImGui::Begin(context, u8"EntityDatas", 10.0f, 0.21f, 0.0f, 0.53f, 1.0f);

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
