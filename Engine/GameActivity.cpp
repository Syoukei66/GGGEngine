#include "GameActivity.h"

// =================================================================
// GGG Statement
// =================================================================
GG_CREATE_FUNC_IMPL(GameActivity)
{
  return true;
}

// =================================================================
// Methods from Activity
// =================================================================
void GameActivity::OnStart()
{
  this->scene_manager_ = new SceneManager();
}

void GameActivity::OnEnd()
{
  this->scene_manager_->ClearScene(this->GetContext());
  delete this->scene_manager_;
  this->scene_manager_ = nullptr;
}

void GameActivity::OnUpdate()
{
  this->scene_manager_->Update(this->GetContext());
}

void GameActivity::OnDraw(const SharedRef<Platform>& platform)
{
  platform->GetGraphicsAPI()->Draw(SharedRef<Activity>(this), [&]()
  {
    this->scene_manager_->Draw(this->GetContext());
  });
}
