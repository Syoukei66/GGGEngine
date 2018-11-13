#include "EntryScene.h"
#include <Native/Windows/Activity/WindowsActivity.h>
#include <Editor/EditorUtils/URI.h>
#include <Director.h>

#include <GUI/FileView/FileView.h>
#include <GUI/EntityView/AssetEntityView.h>
#include <Scene/ViewerScene.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(EntryScene)
{
  this->viewer_scene_ = AssetViewerScene::Create();
  return Scene::Init();
}

// =================================================================
// Methods from Scene
// =================================================================
void EntryScene::OnLoad()
{
}

void EntryScene::OnUnload()
{
}

void EntryScene::OnShow(ISceneShowListener* listener)
{
}

void EntryScene::OnHide(ISceneHideListener* listener)
{
}

void EntryScene::Update()
{
  ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(200.0f, 400.0f), ImGuiSetCond_Once);

  ImGui::Begin("EntryMenu");

  if (ImGui::Button(u8"エクスポート"))
  {
    AssetConverterDirector::Export();
  }
  if (ImGui::Button(u8"プログラム生成"))
  {
    AssetConverterDirector::CreateProgram();
  }

  AssetEntity* selected = FileView::SelectWithImGUI();
  
  if (selected)
  {
    this->selected_entity_ = selected;
  }

  ImGui::End();

  if (AssetEntityView::ShowEntity(this->selected_entity_))
  {
    this->ShowViewer(this->selected_entity_);
  }
}

// =================================================================
// Methods
// =================================================================
void EntryScene::ShowViewer(AssetEntity* entity)
{
  this->viewer_scene_->Run(entity);
}
