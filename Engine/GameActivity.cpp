#include "GameActivity.h"

// =================================================================
// Methods from Activity
// =================================================================
void GameActivity::OnStart()
{
  this->scene_manager_ = new SceneManager();
}

void GameActivity::OnEnd()
{
  this->scene_manager_->ClearScene();
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
    this->scene_manager_->Draw();
  });
}
