#include "Platform.h"

#include <imgui/imgui.h>

// =================================================================
// Methods
// =================================================================
bool Platform::Init(const SharedRef<Activity>& main_activity)
{
  this->graphics_api_ = this->CreateGraphicsAPI();
  this->audio_api_ = this->CreateAudioAPI();
  this->input_api_ = this->CreateInputAPI();
  this->main_activity_ = main_activity;
  this->AddActivity(main_activity);
  return true;
}

bool Platform::Uninit()
{
  this->activity_list_.clear();
  this->main_activity_ = nullptr;
  this->input_api_ = nullptr;
  this->audio_api_ = nullptr;
  this->graphics_api_ = nullptr;
  return true;
}

bool Platform::Update(IApplicationBehavior* app_behavior)
{
  // �v���b�g�t�H�[�����I�����Ă��Ȃ���
  if (!this->ContinueEnabled())
  {
    return false;
  }

  // �t���[�����L����
  if (!this->FrameEnabled())
  {
    return true;
  }

  std::vector<SharedRef<Activity>> delete_activity = std::vector<SharedRef<Activity>>();

  // Activity�̃t���[������
  for (const SharedRef<Activity>& activity : this->activity_list_)
  {
    if (!activity->Update(this->graphics_api_, this->input_api_))
    {
      delete_activity.emplace_back(activity);
    }
  }
  
  // Activity�̍폜����
  for (const SharedRef<Activity>& activity : delete_activity)
  {
    activity->End();
    const auto& itr = std::remove_if(this->activity_list_.begin(), this->activity_list_.end(),
      [&](const SharedRef<Activity>& o) 
      {
        return o == activity;
      }
    );
    this->activity_list_.erase(itr, this->activity_list_.end());
  }

  // GC���쓮������
  GGObjectManager::GC();
  
  return true;
}

// =================================================================
// Setter / Getter
// =================================================================
void Platform::AddActivity(const SharedRef<Activity>& activity)
{
  activity->Start();
  this->activity_list_.emplace_back(activity);
}
