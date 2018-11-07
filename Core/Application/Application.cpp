#include "Application.h"

#include <Core/Application/Activity/Activity.h>
#include <Core/Application/IApplicationBehavior.h>
#include <Core/Application/IPlatformSetting.h>

#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Platform/Platform.h>

#include <Core/Application/Asset/AssetManager.h>

// =================================================================
// Methods
// =================================================================
void Application::Run(IApplicationBehavior* behavior, const IPlatformSetting& platform)
{
  // アプリケーション初期化時イベント
  behavior->OnApplicationBegin();

  // アセット初期化
  AssetManager::Init();

  // アプリケーション初期化
  behavior->SetupApplicationOption(Self().option_);

  // メインアクティビティ初期化
  ActivityOption ao;
  behavior->SetupMainActivityOption(ao);

  Self().main_activity_ = platform.CreateActivity(ao);

  // 各APIの起動処理
  Self().platform_->audio_api_ = platform.CreateAudioAPI();
  Self().platform_->graphics_api_ = platform.CreateGraphicsAPI();
  Self().platform_->input_api_ = platform.CreateInputAPI(Self().option_.input_setting);

  // ゲーム開始処理
  behavior->Init();

  Self().update_event_state_ = UpdateEventState();

  // メインループ
  while (Self().main_activity_->ContinueEnabled())
  {
    if (!Self().main_activity_->FrameEnabled())
    {
      continue;
    }
    Self().update_event_state_.Update();
    Self().platform_->input_api_->Update();
    behavior->Update(Self().update_event_state_);

    // 描画周期が来たら描画を行う
    if (Self().main_activity_->DrawEnabled(Self().update_event_state_.GetDeltaTime()))
    {
      Self().platform_->graphics_api_->Draw(Self().main_activity_, [&]()
      {
        behavior->Draw();
      });
    }

  }

  // アプリケーション終了処理
  behavior->Uninit();

  // アセット終了処理
  AssetManager::Uninit();

  // アセットを含むゲーム側でのリソースの全解放(APIが生きているうちに行う必要があるため)
  GGObjectManager::GC();

  // 各APIの終了処理
  Self().platform_->input_api_ = nullptr;
  Self().platform_->graphics_api_ = nullptr;
  Self().platform_->audio_api_ = nullptr;

  // アクティビティ 解放処理
  Self().main_activity_ = nullptr;

  // システム側でのリソースの全開放
  GGObjectManager::GC();

  // メモリリークチェック
  if (GGObjectManager::CheckLeak())
  {
    GG_ASSERT(false, "未開放のObjectがあります。");
  }

  // アプリケーション終了時イベント
  behavior->OnApplicationEnd();
}
