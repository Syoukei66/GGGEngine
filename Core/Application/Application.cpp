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

  // �A�v���P�[�V�������������C�x���g
  behavior->OnApplicationBegin();

  // �A�Z�b�g������
  AssetManager::Init();

  // �A�v���P�[�V����������
  behavior->SetupApplicationOption(self->option_);

  // �v���b�g�t�H�[�����̋N������
  ActivityOption ao;
  behavior->SetupMainActivityOption(ao);

  self->platform_ = setting->CreatePlatform(self);
  self->platform_->Init(setting->CreateMainActivity(ao));

  // �Q�[���J�n����
  behavior->Init();

  // �A�N�e�B�r�e�B����
  while (self->platform_->Update(behavior));

  // �A�v���P�[�V�����I������
  behavior->Uninit();

  // �A�Z�b�g�I������
  AssetManager::Uninit();

  // �A�Z�b�g���܂ރQ�[�����ł̃��\�[�X�̑S���(API�������Ă��邤���ɍs���K�v�����邽��)
  GGObjectManager::GC();

  // �eAPI�̏I������
  self->platform_->Uninit();
  self->platform_ = nullptr;

  // �A�N�e�B�r�e�B �������
  self->main_activity_ = nullptr;

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

void Application::StartActivity(const SharedRef<Activity>& activity, const SharedRef<Scene>& first_scene)
{
}

bool Application::IsActive()
{
  Application* self = &Self();
  return self->main_activity_->IsActive();
}
