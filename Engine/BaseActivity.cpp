#include "BaseActivity.h"

#include <thread>

#include "Director.h"

#include "../Core/NativeProcess.h"
#include "InputManager.h"
#include "EngineAsset.h"

// =================================================================
// Constructor / Destructor
// =================================================================
BaseActivity::BaseActivity()
{
}

BaseActivity::~BaseActivity()
{
}

// =================================================================
// Method
// =================================================================
bool BaseActivity::Run(IEngineSetting* setting)
{
  Director::SetActivity(this);

  bool result = false;

  setting->OnEngineInit();

  //Engine
  this->engine_ = new Engine();
  Director::SetEngine(this->engine_);
  result = this->engine_->Init(setting);
  NATIVE_ASSERT(result, "エンジンの初期化に失敗しました。");

#ifdef _DEBUG
  NativeProcess::Time::FPS_Init();
#endif

  const EngineOption* option = this->engine_->GetEngineOption();
  this->ApplyEngineOption(option);
  InputManager::GetInstance()->Init(option->input_setting.Build());
  result = this->Init(option);
  //Acitivity
  NATIVE_ASSERT(result, "アクティビティの初期化に失敗しました。");

  setting->OnGameInit();

  EngineAsset::Load();

  //Scene
  engine_->ChangeScene(setting->FirstScene());
  while (this->Update());
  setting->OnGameFinal();

  EngineAsset::Unload();

  OldAssetManager::GetInstance().Uninit();

  result = this->Uninit();
  NATIVE_ASSERT(result, "アクティビティの終了処理に失敗しました。");
  InputManager::GetInstance()->Uninit();

  result = this->engine_->End();
  NATIVE_ASSERT(result, "エンジンの終了処理に失敗しました。");
  delete this->engine_;

  setting->OnEngineFinal();
  
  return true;
}

bool BaseActivity::Update()
{
  if (!this->ContinueEnabled())
  {
    return false;
  }
  if (!this->FrameEnabled())
  {
    return true;
  }

  this->ImGuiNewFrame();

#ifdef _DEBUG
  NativeProcess::Time::FPS_PreUpdate();
#endif

  //TODO:仮、遅延を描画に反映させるかどうかは設定で変えれるように
  //改善案
  // Fixed Update → Engineが定期的に呼び出す
  // Draw → Engineが定期的に呼び出す。
  // Update → Engineが不定期的に呼び出す。経過時間DeltaTimeを取得しうまく処理する
  //のようにしてみてはどうか
  const int second_elapsed = 1000 / 60; //仮実装

  InputManager::GetInstance()->ClearCaches();
  UpdateEventState::GetInstance()->Update(second_elapsed);

  EngineInputState::GetInstance()->Prepare();
  this->InputProcess(EngineInputState::GetInstance());

  //std::thread update_thread(&Engine::OnUpdate, this->engine_);
  //std::thread draw_thread(&BaseActivity::Draw, this);
  //update_thread.join();
  //draw_thread.join();

  this->engine_->OnUpdate();
  this->Draw();

  this->ImGuiEndFrame();

#ifdef _DEBUG
  NativeProcess::Time::FPS_PostUpdate();
#endif

  OldAssetManager::GetInstance().Update();
  return true;
}

bool BaseActivity::Draw()
{
  if (!this->engine_->DrawWait())
  {
    return false;
  }
  if (!this->PreDraw())
  {
    return false;
  }
  NativeProcess::Graphics::SetViewport(0.0f, 0.0f, this->engine_->GetScreenWidth(), this->engine_->GetScreenHeight(), 0.0f, 1.0f);
  NativeProcess::Graphics::ViewportClear();
  this->engine_->OnDraw();
  this->PostDraw();
  return true;
}
