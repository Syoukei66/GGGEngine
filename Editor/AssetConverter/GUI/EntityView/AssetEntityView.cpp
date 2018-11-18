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
  ImGui::Text((u8"�t�@�C���� : " + uri.GetPrefix()).c_str());
  ImGui::Text((u8"UniqueID : " + std::to_string(meta->GetUniqueID())).c_str());
  ImGui::Text((u8"���̓f�B���N�g�� : " + FileUtil::CreateSolutionPath(meta->GetInputPath())).c_str());
  ImGui::Text((u8"�o�̓f�B���N�g�� : " + FileUtil::CreateSolutionPath(meta->GetOutputPath())).c_str());
  ImGui::Text((u8"�^�C���X�^���v : " + meta->GetTimeStamp()).c_str());

  bool open_viewer = ImGui::Button(u8"�r���[���[���N��");

  ImGui::End();

  return open_viewer;
}

void AssetEntityView::StartViewer(const SharedRef<AssetEntity>& entity)
{

}
