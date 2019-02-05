#include "EntryScene.h"
#include <Editor/EditorUtils/URI.h>
#include <Director.h>

#include <GUI/FileView/FileView.h>
#include <GUI/EntityView/AssetEntityView.h>
#include <Scene/ViewerScene.h>
#include <GUI/FileView/FileView.h>
#include <Native/Windows/Activity/WindowActivityContext.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(EntryScene, AssetConverterContext* context)
{
  this->context_ = context;
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

void EntryScene::OnShow()
{
  this->context_->Fetch();
  FileView::Init(this->context_);
}

void EntryScene::OnHide()
{
  FileView::Uninit();
}

void EntryScene::Update(const ActivityContext& context)
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
  const SharedRef<AssetViewerScene>& scene = AssetViewerScene::Create(this->context_, entity);
  if (!scene)
  {
    return;
  }
  ActivityOption op = ActivityOption();
  op.activity_name = "編集ウィンドウ";
  op.resize_window = true;
  op.sub_window = true;
  op.window_size = Application::GetMainActivity()->GetContext().GetScreenSize();
  const SharedRef<GameActivity>& activity = GameActivity::Create();
  Application::StartActivity(activity, op);
  activity->ChangeScene(scene);
}
