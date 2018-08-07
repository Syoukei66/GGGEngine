#include "BaseActivity.h"

#include <thread>

#include "Director.h"

#include "../Common/NativeProcess.h"
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

  bool result = false;

  setting->OnEngineInit();

  //Engine
  this->engine_ = new Engine();
  Director::GetInstance()->SetEngine(this->engine_);
  result = this->engine_->Init(setting);
  NATIVE_ASSERT(result, "�G���W���̏������Ɏ��s���܂����B");

#ifdef _DEBUG
  NativeProcess::Time::FPS_Init();
#endif

  const EngineOption* option = this->engine_->GetEngineOption();
  this->ApplyEngineOption(option);
  InputManager::GetInstance()->Init(option->input_setting.Build());
  result = this->Init(option);
  //Acitivity
  NATIVE_ASSERT(result, "�A�N�e�B�r�e�B�̏������Ɏ��s���܂����B");

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
  NATIVE_ASSERT(result, "�A�N�e�B�r�e�B�̏I�������Ɏ��s���܂����B");
  InputManager::GetInstance()->Uninit();

  result = this->engine_->End();
  NATIVE_ASSERT(result, "�G���W���̏I�������Ɏ��s���܂����B");
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

  //TODO:���A�x����`��ɔ��f�����邩�ǂ����͐ݒ�ŕς����悤��
  //���P��
  // Fixed Update �� Engine������I�ɌĂяo��
  // Draw �� Engine������I�ɌĂяo���B
  // Update �� Engine���s����I�ɌĂяo���B�o�ߎ���DeltaTime���擾�����܂���������
  //�̂悤�ɂ��Ă݂Ă͂ǂ���
  const int second_elapsed = 1000 / 60; //������

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
  NativeProcess::Graphics::SetViewport(0.0f, 0.0f, this->engine_->GetScreenWidth(), this->engine_->GetScreenHeight(), 0.0f, 1.0f);
  NativeProcess::Graphics::ViewportClear();
  this->engine_->OnDraw();
  this->PostDraw();
  return true;
}
