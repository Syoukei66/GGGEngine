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
  // �A�v���P�[�V�������������C�x���g
  behavior->OnApplicationBegin();

  // �A�Z�b�g������
  AssetManager::Init();

  // �A�v���P�[�V����������
  behavior->SetupApplicationOption(Self().option_);

  // ���C���A�N�e�B�r�e�B������
  ActivityOption ao;
  behavior->SetupMainActivityOption(ao);

  Self().main_activity_ = platform.CreateActivity(ao);

  // �eAPI�̋N������
  Self().platform_->audio_api_ = platform.CreateAudioAPI();
  Self().platform_->graphics_api_ = platform.CreateGraphicsAPI();
  Self().platform_->input_api_ = platform.CreateInputAPI(Self().option_.input_setting);

  // �Q�[���J�n����
  behavior->Init();

  Self().update_event_state_ = UpdateEventState();

  // ���C�����[�v
  while (Self().main_activity_->ContinueEnabled())
  {
    if (!Self().main_activity_->FrameEnabled())
    {
      continue;
    }
    Self().update_event_state_.Update();
    Self().platform_->input_api_->Update();
    behavior->Update(Self().update_event_state_);

    // �`�������������`����s��
    if (Self().main_activity_->DrawEnabled(Self().update_event_state_.GetDeltaTime()))
    {
      Self().platform_->graphics_api_->Draw(Self().main_activity_, [&]()
      {
        behavior->Draw();
      });
    }

  }

  // �A�v���P�[�V�����I������
  behavior->Uninit();

  // �A�Z�b�g�I������
  AssetManager::Uninit();

  // �A�Z�b�g���܂ރQ�[�����ł̃��\�[�X�̑S���(API�������Ă��邤���ɍs���K�v�����邽��)
  GGObjectManager::GC();

  // �eAPI�̏I������
  Self().platform_->input_api_ = nullptr;
  Self().platform_->graphics_api_ = nullptr;
  Self().platform_->audio_api_ = nullptr;

  // �A�N�e�B�r�e�B �������
  Self().main_activity_ = nullptr;

  // �V�X�e�����ł̃��\�[�X�̑S�J��
  GGObjectManager::GC();

  // ���������[�N�`�F�b�N
  if (GGObjectManager::CheckLeak())
  {
    GG_ASSERT(false, "���J����Object������܂��B");
  }

  // �A�v���P�[�V�����I�����C�x���g
  behavior->OnApplicationEnd();
}
