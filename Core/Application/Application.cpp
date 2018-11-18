#include "Application.h"

#include <Core/Application/Activity/Activity.h>
#include <Core/Application/IApplicationBehavior.h>
#include <Core/Application/IApplicationSetting.h>

#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Platform/Platform.h>

#include <Core/Application/Asset/AssetManager.h>

#include <imgui/imgui_ja_gryph_ranges.h>
#include <imgui/imgui.h>

// =================================================================
// Methods
// =================================================================
void Application::Run(IApplicationBehavior* behavior, IApplicationSetting* setting)
{
  Application* self = &Self();

  // アプリケーション初期化時イベント
  behavior->OnApplicationBegin();

  // アセット初期化
  AssetManager::Init();

  // アプリケーション初期化
  behavior->SetupApplicationOption(self->option_);

  // プラットフォーム側の起動処理
  ActivityOption ao;
  behavior->SetupMainActivityOption(ao);

  self->platform_ = Platform::Create();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  
  setting->SetupApplication(self, ao, &self->main_activity_, &self->platform_->graphics_api_, &self->platform_->input_api_, &self->platform_->audio_api_);

  ImGui::StyleColorsDark();
  ImGui::SetupJapaneseString();

  // ゲーム開始処理
  behavior->Init();

  self->update_event_state_ = UpdateEventState();

  // メインループ
  while (self->main_activity_->ContinueEnabled())
  {
    if (!self->main_activity_->FrameEnabled())
    {
      continue;
    }
    self->platform_->graphics_api_->ImGuiNewFrame();
    ImGui::NewFrame();

    self->update_event_state_.Update();
    self->platform_->input_api_->Update();
    behavior->Update(self->update_event_state_);

    // 描画周期が来たら描画を行う
    if (self->main_activity_->DrawEnabled(self->update_event_state_.GetDeltaTime()))
    {
      ImGui::Render();
      self->platform_->graphics_api_->Draw(self->main_activity_, [&]()
      {
        behavior->Draw();
      });
    }

    self->platform_->graphics_api_->ImGuiEndFrame();
    GGObjectManager::GC();
  }

  // アプリケーション終了処理
  behavior->Uninit();

  // アセット終了処理
  AssetManager::Uninit();

  // アセットを含むゲーム側でのリソースの全解放(APIが生きているうちに行う必要があるため)
  GGObjectManager::GC();

  // 各APIの終了処理
  self->platform_->input_api_ = nullptr;
  self->platform_->graphics_api_ = nullptr;
  self->platform_->audio_api_ = nullptr;

  self->platform_ = nullptr;

  // アクティビティ 解放処理
  self->main_activity_ = nullptr;

  // システム側でのリソースの全開放
  GGObjectManager::GC();

  ImGui::DestroyContext();

  // メモリリークチェック
  if (GGObjectManager::CheckLeak())
  {
    GG_ASSERT(false, "未開放のObjectがあります。");
  }

  // アプリケーション終了時イベント
  behavior->OnApplicationEnd();
}

bool Application::IsActive()
{
  Application* self = &Self();
  return self->main_activity_->IsActive();
}
