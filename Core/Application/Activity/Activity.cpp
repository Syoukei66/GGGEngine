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

void Activity::EndActivity()
{
  this->OnEnd();
}

void Activity::EndContext()
{
  this->context_->End();
  this->context_ = nullptr;
}

bool Activity::Update(const SharedRef<Platform>& platform)
{
  // Activity‚ªI—¹‚µ‚Ä‚¢‚½‚çfalse‚ÅƒŠƒ^[ƒ“
  if (!this->context_->IsEnabled())
  {
    return false;
  }
  this->context_->NewFrame(platform);
  this->OnUpdate();
  // •`‰æŽüŠú‚ª—ˆ‚½‚ç•`‰æ‚ðs‚¤
  if (this->context_->IsVisible() && this->context_->DrawEnabled())
  {
    this->OnDraw(platform);
  }
  this->context_->EndFrame();
  return true;
}
