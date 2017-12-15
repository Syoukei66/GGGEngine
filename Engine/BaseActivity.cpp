#include "BaseActivity.h"
#include "Director.h"

#include "NativeMethod.h"
#include "TexturePaletteManager.h"
#include "InputManager.h"
#include <string.h>

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
  Director::GetInstance()->SetActivity(this);
  NativeMethod::Graphics_SetInstance(this->SetupNativeProcess_Graphics());
  NativeMethod::Matrix_SetInstance(this->SetupNativeProcess_Matrix());
  NativeMethod::Texture_SetInstance(this->SetupNativeProcess_Texture());
  NativeMethod::Material_SetInstance(this->SetupNativeProcess_Material());
  NativeMethod::Model_SetInstance(this->SetupNativeProcess_Model());
  NativeMethod::IO_SetInstance(this->SetupNativeProcess_IO());
  NativeMethod::Time_SetInstance(this->SetupNativeProcess_Time());

  //Engine
  this->engine_ = new Engine();
  Director::GetInstance()->SetEngine(this->engine_);
  NATIVE_ASSERT(this->engine_->Init(setting), "エンジンの初期化に失敗しました。");

#ifdef _DEBUG
  NativeMethod::Time().FPS_Init();
#endif

  const EngineOption* option = this->engine_->GetEngineOption();
  this->ApplyEngineOption(option);
  InputManager::GetInstance()->Init(option->input_setting.Build());
  //Acitivity
  NATIVE_ASSERT(this->Init(option), "アクティビティの初期化に失敗しました。");

  setting->OnGameInit();
  //Scene
  engine_->ChangeScene(setting->FirstScene());
  while (this->Update());
  setting->OnGameFinal();

  NATIVE_ASSERT(this->Uninit(), "アクティビティの終了処理に失敗しました。");
  InputManager::GetInstance()->Uninit();

  NATIVE_ASSERT(this->engine_->End(), "エンジンの終了処理に失敗しました。");
  delete this->engine_;
  
  NativeMethod::Graphics_DeleteInstance();
  NativeMethod::Matrix_DeleteInstance();
  NativeMethod::Texture_DeleteInstance();
  NativeMethod::Material_DeleteInstance();
  NativeMethod::Model_DeleteInstance();
  NativeMethod::IO_DeleteInstance();
  NativeMethod::Time_DeleteInstance();
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

#ifdef _DEBUG
  NativeMethod::Time().FPS_PreUpdate();
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

  this->engine_->OnUpdate();
  if (this->engine_->DrawWait())
  {
    if (this->PreDraw())
    {
      this->engine_->OnDraw();
      this->PostDraw();
    }
    this->DrawToScreen();
  }

#ifdef _DEBUG
  NativeMethod::Time().FPS_PostUpdate();
#endif

  return true;
}
