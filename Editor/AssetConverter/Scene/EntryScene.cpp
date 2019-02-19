#include "EntryScene.h"
#include <Editor/EditorUtils/URI.h>
#include <Director.h>

#include <GUI/FileView/FileView.h>
#include <GUI/EntityView/AssetEntityView.h>
#include <Scene/ViewerScene.h>
#include <GUI/FileView/FileView.h>
#include <Native/Windows/Activity/WindowActivityContext.h>
#include <Scene/AssetViewer/AssetViewerScene.h>
#include <Engine/GameActivity.h>
#include <Util/ImGuiUtil.h>

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
void EntryScene::OnLoad(const ActivityContext& context)
{
}

void EntryScene::OnUnload(const ActivityContext& context)
{
}

void EntryScene::OnShow(const ActivityContext& context)
{
  this->context_->Fetch();
  FileView::Init(this->context_);
}

void EntryScene::OnHide(const ActivityContext& context)
{
  FileView::Uninit();
}

void EntryScene::Update(const ActivityContext& context)
{
  ImGui::Begin(context, u8"EntryMenu", 10.0f, 0.0f, 0.0f, 0.2f, 0.5f);
  if (ImGui::Button(u8"エクスポート"))
  {
    AssetConverterDirector::Export();
  }
  if (ImGui::Button(u8"プログラム生成"))
  {
    AssetConverterDirector::CreateProgram();
  }

  const SharedRef<AssetEntity>& selected = FileView::SelectWithImGUI(context, this->context_);
  
  if (selected)
  {
    this->selected_entity_ = selected;
  }

  ImGui::End();

  if (AssetEntityView::ShowEntity(context, this->selected_entity_))
  {
    this->ShowViewer(this->selected_entity_);
    this->selected_entity_ = nullptr;
  }

  this->elapsed_time_since_fetch_ += Application::GetUpdateEventState().GetDeltaTime();
  if (this->elapsed_time_since_fetch_ > 5.0f)
  {
    this->context_->Fetch();
    FileView::Init(this->context_);
    this->elapsed_time_since_fetch_ = 0.0f;
  }
}

// =================================================================
// Methods
// =================================================================
void EntryScene::OnReload()
{
  this->context_->Fetch();
  FileView::Init(this->context_);
}

void EntryScene::ShowViewer(const SharedRef<AssetEntity>& entity)
{
  const SharedRef<AssetViewerScene>& scene = AssetViewerScene::Create(SharedRef<EntryScene>(this), this->context_, entity);
  if (!scene)
  {
    return;
  }
  ActivityOption op = ActivityOption();
  op.activity_name = entity->GetMetaData()->GetURI().GetFullPath().c_str();
  op.resize_window = false;
  op.sub_window = true;
  op.window_size = Application::GetMainActivity()->GetContext().GetScreenSize();
  const SharedRef<GameActivity>& activity = GameActivity::Create();
  Application::StartActivity(activity, op);
  activity->ChangeScene(scene);
}
