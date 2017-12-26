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
  NativeMethod::Texture_SetInstance(this->SetupNativeProcess_Texture());
  NativeMethod::Material_SetInstance(this->SetupNativeProcess_Material());
  NativeMethod::Model_SetInstance(this->SetupNativeProcess_Model());
  NativeMethod::IO_SetInstance(this->SetupNativeProcess_IO());
  NativeMethod::Time_SetInstance(this->SetupNativeProcess_Time());

  bool result = false;

  //Engine
  this->engine_ = new Engine();
  Director::GetInstance()->SetEngine(this->engine_);
  result = this->engine_->Init(setting);
  NATIVE_ASSERT(result, "�G���W���̏������Ɏ��s���܂����B");

#ifdef _DEBUG
  NativeMethod::Time().FPS_Init();
#endif

  const EngineOption* option = this->engine_->GetEngineOption();
  this->ApplyEngineOption(option);
  InputManager::GetInstance()->Init(option->input_setting.Build());
  result = this->Init(option);
  //Acitivity
  NATIVE_ASSERT(result, "�A�N�e�B�r�e�B�̏������Ɏ��s���܂����B");

  setting->OnGameInit();
  //Scene
  engine_->ChangeScene(setting->FirstScene());
  while (this->Update());
  setting->OnGameFinal();

  result = this->Uninit();
  NATIVE_ASSERT(result, "�A�N�e�B�r�e�B�̏I�������Ɏ��s���܂����B");
  InputManager::GetInstance()->Uninit();

  result = this->engine_->End();
  NATIVE_ASSERT(result, "�G���W���̏I�������Ɏ��s���܂����B");
  delete this->engine_;
  
  NativeMethod::Graphics_DeleteInstance();
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