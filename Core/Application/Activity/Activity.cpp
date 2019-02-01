#include "Activity.h"

// =================================================================
// Methods
// =================================================================
void Activity::Start(const ActivityOption& ao, const SharedRef<ActivityContext>& context)
{
  this->context_ = context;
  this->context_->Start(ao);
  this->OnStart();
}

void Activity::End()
{
  this->OnEnd();
  this->context_->End();
  this->context_ = nullptr;
}

bool Activity::Update(const SharedRef<Platform>& platform)
{
  this->context_->NewFrame(platform);
  this->OnUpdate();
  // •`‰æŽüŠú‚ª—ˆ‚½‚ç•`‰æ‚ðs‚¤
  if (this->context_->DrawEnabled())
  {
    this->OnDraw(platform);
  }
  this->context_->EndFrame();
  return true;
}
