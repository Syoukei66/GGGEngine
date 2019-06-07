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

  // �A�v���P�[�V�������������C�x���g
  behavior->OnApplicationBegin();

  // �A�Z�b�g������
  AssetManager::Init();

  // �A�v���P�[�V����������
  behavior->SetupApplicationOption(self->option_);

  // �v���b�g�t�H�[�����̋N������
  behavior->SetupMainActivityOption(self->option_.main_activity_option);

  // ����������
  self->Init(platform, behavior, self->option_);

  while (self->Update());

  // �����̎Q�ƃJ�E���g������
  const_cast<SharedRef<Platform>&>(platform) = nullptr;

  // �I������
  self->Uninit(behavior);

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

  // �A�v���P�[�V�����J�n����
  behavior->Init();

  return true;
}

bool Application::Uninit(IApplicationBehavior* behavior)
{
  Application* self = &Self();
 
  behavior->Uninit();

  // �A�Z�b�g�I������
  AssetManager::Uninit();

  // �A�Z�b�g���܂ރQ�[�����ł̃��\�[�X�̑S���(API�������Ă��邤���ɍs���K�v�����邽��)
  GGObjectManager::GC();

  delete self->update_event_state_;

  // �A�N�e�B�r�e�B�I������
  for (auto& pair : self->sub_activities_)
  {
    pair.second->EndActivity();
  }

  GGObjectManager::GC();

  // �eAPI�̏I������
  // API�����C���A�N�e�B�r�e�B�̃R���e�L�X�g�Ɉˑ����Ă���̂�
  // ���API�I���������s��
  self->platform_->Uninit();
  self->platform_ = nullptr;

  GGObjectManager::GC();

  // �A�N�e�B�r�e�B�̃R���e�L�X�g�̏I������
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

  // �v���b�g�t�H�[�����I�����Ă��Ȃ���
  if (!self->GetPlatform()->ContinueEnabled())
  {
    return false;
  }

  // �t���[�����L����
  if (!self->GetPlatform()->FrameEnabled())
  {
    return true;
  }

  self->update_event_state_->Update();

  std::vector<SharedRef<Activity>> delete_activity = std::vector<SharedRef<Activity>>();

  // Activity�̃t���[������
  for (auto& pair : self->sub_activities_)
  {
    if (!pair.second->Update(self->platform_))
    {
      // Application�ȊO�ɊǗ�����Ă��Ȃ�������
      if (pair.second->GetReferenceCount() == 1)
      {
        delete_activity.emplace_back(pair.second);
      }
    }
  }

  // Activity�̍폜����
  for (const SharedRef<Activity>& activity : delete_activity)
  {
    const T_UINT64 id = activity->GetContext().GetActivityID();
    activity->EndActivity();
    activity->EndContext();
    self->sub_activities_.erase(id);
  }

  // GC���쓮������
  GGObjectManager::GC();

  return true;
}
