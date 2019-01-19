#include "EntryScene.h"
#include <Native/Windows/Activity/WindowsActivity.h>
#include <Editor/EditorUtils/URI.h>
#include <Director.h>

#include <GUI/FileView/FileView.h>
#include <GUI/EntityView/AssetEntityView.h>
#include <Scene/ViewerScene.h>
#include <GUI/FileView/FileView.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(EntryScene, AssetConverterContext* context)
{
  this->viewer_scene_ = AssetViewerScene::Create();
  this->context_ = context;
  return Scene::Init();
}

// =================================================================
// Methods from Scene
// =================================================================
void EntryScene::OnLoad()
{
  this->viewer_scene_->Load();
}

void EntryScene::OnUnload()
{
  this->viewer_scene_->Unload();
}

void EntryScene::OnShow()
{
  FileView::Init(this->context_);
}

void EntryScene::OnHide()
{
  FileView::Uninit();
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

  const SharedRef<AssetEntity>& selected = FileView::SelectWithImGUI();
  
  if (selected)
  {
    this->selected_entity_ = selected;
  }

  ImGui::End();

  if (AssetEntityView::ShowEntity(this->selected_entity_))
  {
    this->ShowViewer(this->selected_entity_);
    this->selected_entity_ = nullptr;
  }
}

// =================================================================
// Methods
// =================================================================
void EntryScene::ShowViewer(const SharedRef<AssetEntity>& entity)
{
  this->viewer_scene_->Run(entity, this->context_);
}
