#include "Application.h"

#include <Core/Application/Activity/Activity.h>
#include <Core/Application/IApplicationBehavior.h>
#include <Core/Application/IApplicationSetting.h>

#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Platform/Platform.h>

#include <Core/Application/Asset/AssetManager.h>

#include <imgui/imgui_ja_gryph_ranges.h>
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

  self->platform_ = Platform::Create();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  
  setting->SetupApplication(self, ao, &self->main_activity_, &self->platform_->graphics_api_, &self->platform_->input_api_, &self->platform_->audio_api_);

  ImGui::StyleColorsDark();
  ImGui::SetupJapaneseString();

  // �Q�[���J�n����
  behavior->Init();

  self->update_event_state_ = UpdateEventState();

  // ���C�����[�v
  while (self->main_activity_->ContinueEnabled())
  {
    if (!self->main_activity_->FrameEnabled())
    {
      continue;
    }
    self->platform_->graphics_api_->ImGuiNewFrame();
    ImGui::NewFrame();

    self->update_event_state_.Update();
    self->platform_->input_api_->Update();
    behavior->Update(self->update_event_state_);

    // �`�������������`����s��
    if (self->main_activity_->DrawEnabled(self->update_event_state_.GetDeltaTime()))
    {
      ImGui::Render();
      self->platform_->graphics_api_->Draw(self->main_activity_, [&]()
      {
        behavior->Draw();
      });
    }

    self->platform_->graphics_api_->ImGuiEndFrame();
    GGObjectManager::GC();
  }

  // �A�v���P�[�V�����I������
  behavior->Uninit();

  // �A�Z�b�g�I������
  AssetManager::Uninit();

  // �A�Z�b�g���܂ރQ�[�����ł̃��\�[�X�̑S���(API�������Ă��邤���ɍs���K�v�����邽��)
  GGObjectManager::GC();

  // �eAPI�̏I������
  self->platform_->input_api_ = nullptr;
  self->platform_->graphics_api_ = nullptr;
  self->platform_->audio_api_ = nullptr;

  self->platform_ = nullptr;

  // �A�N�e�B�r�e�B �������
  self->main_activity_ = nullptr;

  // �V�X�e�����ł̃��\�[�X�̑S�J��
  GGObjectManager::GC();

  ImGui::DestroyContext();

  // ���������[�N�`�F�b�N
  if (GGObjectManager::CheckLeak())
  {
    GG_ASSERT(false, "���J����Object������܂��B");
  }

  // �A�v���P�[�V�����I�����C�x���g
  behavior->OnApplicationEnd();
}

bool Application::IsActive()
{
  Application* self = &Self();
  return self->main_activity_->IsActive();
}
