#include "AssetEntityView.h"
#include <Entity/AssetEntity.h>
#include <Entity/AssetInfo.h>

// =================================================================
// Methods
// =================================================================
void AssetEntityView::ShowEntity(AssetEntity* entity)
{
  if (!entity)
  {
    return;
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

  if (ImGui::Button(u8"ビューワーを起動"))
  {
    StartViewer(entity);
  }

  ImGui::End();
}

void AssetEntityView::StartViewer(AssetEntity* entity)
{
  switch (entity->GetID())
  {
    // Mesh
  case AssetEntity::EntityID::ID_DEFAULT_MESH:
    break;
  case AssetEntity::EntityID::ID_MODEL_MESH:
    break;
    // Material
  case AssetEntity::EntityID::ID_DEFAULT_MATERIAL:
    break;
  case AssetEntity::EntityID::ID_MODEL_MATERIAL:
    break;
    // Texture
  case AssetEntity::EntityID::ID_TEXTURE:
    break;
    // Text
  case AssetEntity::EntityID::ID_CSV:
    break;
  case AssetEntity::EntityID::ID_JSON:
    break;
    // Shader
  case AssetEntity::EntityID::ID_SHADER:
    break;
    // Sound
  case AssetEntity::EntityID::ID_SOUND:
    break;
    // Model
  case AssetEntity::EntityID::ID_MODEL:
    break;
  }
}
