#include "BaseActivity.h"

#include <thread>

#include "Director.h"

#include "NativeMethod.h"
#include "InputManager.h"

#include "EngineResourcePool.h"
#include "EngineAsset.h"

#include "EngineResourcePool.h"
#include "UserResourcePool.h"

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
  NativeMethod::IO_SetInstance(this->SetupNativeProcess_IO());
  NativeMethod::Time_SetInstance(this->SetupNativeProcess_Time());

  bool result = false;

  setting->OnEngineInit();

  //Engine
  this->engine_ = new Engine();
  Director::GetInstance()->SetEngine(this->engine_);
  result = this->engine_->Init(setting);
  NATIVE_ASSERT(result, "エンジンの初期化に失敗しました。");

#ifdef _DEBUG
  NativeMethod::Time().FPS_Init();
#endif

  this->fbx_manager_ = FbxManager::Create();

  const EngineOption* option = this->engine_->GetEngineOption();
  this->ApplyEngineOption(option);
  InputManager::GetInstance()->Init(option->input_setting.Build());
  result = this->Init(option);
  //Acitivity
  NATIVE_ASSERT(result, "アクティビティの初期化に失敗しました。");

  EngineResourcePool::GetInstance().Init();
  UserResourcePool::GetInstance().Init();

  setting->OnGameInit();

  IResourceLoadingListener listener = IResourceLoadingListener();

  EngineResourcePool& pool = EngineResourcePool::GetInstance();
  pool.ReserveLoad(EngineAsset::Shader::DEFAULT);
  pool.ReserveLoad(EngineAsset::Shader::LAMBERT);
  pool.ReserveLoad(EngineAsset::Shader::PHONG);
  pool.ReserveLoad(EngineAsset::Shader::PARTICLE);
  pool.ReserveLoad(EngineAsset::Shader::PRIMITIVE);
  pool.ReserveLoad(EngineAsset::Shader::SPRITE);
  pool.ReserveLoad(EngineAsset::Shader::WHITE);

  pool.PreRealize(&listener);
  pool.Realize(&listener);

  EngineAsset::Mesh::CUBE.Load();
  EngineAsset::Mesh::PLANE.Load();
  EngineAsset::Mesh::QUAD.Load();

  //Scene
  engine_->ChangeScene(setting->FirstScene());
  while (this->Update());
  setting->OnGameFinal();

  UserResourcePool::GetInstance().Uninit();
  EngineResourcePool::GetInstance().Uninit();

  result = this->Uninit();
  NATIVE_ASSERT(result, "アクティビティの終了処理に失敗しました。");
  InputManager::GetInstance()->Uninit();

  this->fbx_manager_->Destroy();

  result = this->engine_->End();
  NATIVE_ASSERT(result, "エンジンの終了処理に失敗しました。");
  delete this->engine_;

  setting->OnEngineFinal();
  
  NativeMethod::Graphics_DeleteInstance();
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

  this->ImGuiNewFrame();

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

  //std::thread update_thread(&Engine::OnUpdate, this->engine_);
  //std::thread draw_thread(&BaseActivity::Draw, this);
  //update_thread.join();
  //draw_thread.join();

  this->engine_->OnUpdate();
  this->Draw();

  this->ImGuiEndFrame();

#ifdef _DEBUG
  NativeMethod::Time().FPS_PostUpdate();
#endif

  UserResourcePool::GetInstance().Update();
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
  NativeMethod::Graphics().Graphics_SetViewport(0.0f, 0.0f, this->engine_->GetScreenWidth(), this->engine_->GetScreenHeight(), 0.0f, 1.0f);
  NativeMethod::Graphics().Graphics_Clear();
  this->engine_->OnDraw();
  this->PostDraw();
  return true;
}
