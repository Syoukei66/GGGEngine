#include "Application.h"

#include <Core/Application/Activity/Activity.h>
#include <Core/Application/IApplicationBehavior.h>
#include <Core/Application/IApplicationSetting.h>

#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Platform/Platform.h>

#include <Core/Application/Asset/AssetManager.h>

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

  self->platform_ = setting->CreatePlatform(self);
  self->platform_->Init(setting->CreateMainActivity(ao));

  // ゲーム開始処理
  behavior->Init();

  // アクティビティ処理
  while (self->platform_->Update(behavior));

  // アプリケーション終了処理
  behavior->Uninit();

  // アセット終了処理
  AssetManager::Uninit();

  // アセットを含むゲーム側でのリソースの全解放(APIが生きているうちに行う必要があるため)
  GGObjectManager::GC();

  // 各APIの終了処理
  self->platform_->Uninit();
  self->platform_ = nullptr;

  // アクティビティ 解放処理
  self->main_activity_ = nullptr;

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

void Application::StartActivity(const SharedRef<Activity>& activity, const SharedRef<Scene>& first_scene)
{
}

bool Application::IsActive()
{
  Application* self = &Self();
  return self->main_activity_->IsActive();
}
