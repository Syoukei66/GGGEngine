#include "Application.h"

#include <Core/Application/Activity/Activity.h>
#include <Core/Application/IApplicationBehavior.h>
#include <Core/Application/IApplicationSetting.h>

#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Platform/Platform.h>

#include <Core/Application/Asset/AssetManager.h>

// =================================================================
// Methods
// =================================================================
void Application::Run(IApplicationBehavior* behavior, const SharedRef<Platform>& platform)
{
  Application* self = &Self();

  self->behavior_ = behavior;

  // アプリケーション初期化時イベント
  behavior->OnApplicationBegin();

  // アセット初期化
  AssetManager::Init();

  // アプリケーション初期化
  behavior->SetupApplicationOption(self->option_);

  // プラットフォーム側の起動処理
  behavior->SetupMainActivityOption(self->option_.main_activity_option);

  // 初期化処理
  self->Init(platform, behavior, self->option_);

  while (self->Update());

  // 引数の参照カウントを消す
  const_cast<SharedRef<Platform>&>(platform) = nullptr;

  // 終了処理
  self->Uninit(behavior);

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

SharedRef<Activity> Application::StartActivity(const SharedRef<Activity>& activity, const ActivityOption& ao)
{
  Application* self = &Self();

  ActivityContext* context = self->platform_->CreateActivityContext();
  activity->Start(ao, self->option_.input_setting, context);
  self->platform_->GetGraphicsAPI()->CreateSubActivityResources(activity);
  self->platform_->GetInputAPI()->CreateSubActivityResources(activity);
  self->sub_activities_[context->GetActivityID()] = activity;
  return activity;
}

bool Application::Init(const SharedRef<Platform>& platform, IApplicationBehavior* behavior, const ApplicationOption& option)
{
  Application* self = &Self();

  self->platform_ = platform;

  ActivityContext* context = self->GetPlatform()->CreateActivityContext();
  self->main_activity_ = behavior->CreateMainActivity();
  self->main_activity_->Start(option.main_activity_option, self->option_.input_setting, context);
  self->sub_activities_[context->GetActivityID()] = self->main_activity_;

  self->platform_->Init(self->option_);

  self->update_event_state_ = new UpdateEventState();

  // アプリケーション開始処理
  behavior->Init();

  return true;
}

bool Application::Uninit(IApplicationBehavior* behavior)
{
  Application* self = &Self();
 
  behavior->Uninit();

  // アセット終了処理
  AssetManager::Uninit();

  // アセットを含むゲーム側でのリソースの全解放(APIが生きているうちに行う必要があるため)
  GGObjectManager::GC();

  delete self->update_event_state_;

  // アクティビティ終了処理
  for (auto& pair : self->sub_activities_)
  {
    pair.second->EndActivity();
  }

  GGObjectManager::GC();

  // 各APIの終了処理
  // APIがメインアクティビティのコンテキストに依存しているので
  // 先にAPI終了処理を行う
  self->platform_->Uninit();
  self->platform_ = nullptr;

  GGObjectManager::GC();

  // アクティビティのコンテキストの終了処理
  for (auto& pair : self->sub_activities_)
  {
    pair.second->EndContext();
  }
  self->sub_activities_.clear();
  self->main_activity_ = nullptr;

  return true;
}

bool Application::Update()
{
  Application* self = &Self();

  // プラットフォームが終了していないか
  if (!self->GetPlatform()->ContinueEnabled())
  {
    return false;
  }

  // フレームが有効か
  if (!self->GetPlatform()->FrameEnabled())
  {
    return true;
  }

  self->update_event_state_->Update();

  std::vector<SharedRef<Activity>> delete_activity = std::vector<SharedRef<Activity>>();

  // Activityのフレーム処理
  for (auto& pair : self->sub_activities_)
  {
    if (!pair.second->Update(self->platform_))
    {
      // Application以外に管理されていなかったら
      if (pair.second->GetReferenceCount() == 1)
      {
        delete_activity.emplace_back(pair.second);
      }
    }
  }

  // Activityの削除処理
  for (const SharedRef<Activity>& activity : delete_activity)
  {
    const T_UINT64 id = activity->GetContext().GetActivityID();
    activity->EndActivity();
    activity->EndContext();
    self->sub_activities_.erase(id);
  }

  // GCを作動させる
  GGObjectManager::GC();

  return true;
}
