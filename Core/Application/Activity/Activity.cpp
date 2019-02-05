#include "Activity.h"

// =================================================================
// Methods
// =================================================================
void Activity::Start(const ActivityOption& ao, const InputSetting& setting, ActivityContext* context)
{
  this->context_ = context;
  this->context_->Start(ao, setting);
  this->OnStart();
}

void Activity::EndActivity()
{
  this->OnEnd();
}

void Activity::EndContext()
{
  this->context_->End();
  delete this->context_;
  this->context_ = nullptr;
}

bool Activity::Update(const SharedRef<Platform>& platform)
{
  // Activity���I�����Ă�����false�Ń��^�[��
  if (!this->context_->IsEnabled())
  {
    return false;
  }
  this->context_->NewFrame(SharedRef<Activity>(this), platform);
  this->OnUpdate();
  // �`�������������`����s��
  if (this->context_->IsVisible() && this->context_->DrawEnabled())
  {
    this->OnDraw(platform);
  }
  this->context_->EndFrame();
  return true;
}
