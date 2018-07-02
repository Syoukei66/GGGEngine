#include "GameObjectRenderState.h"

#include "GameObject.h"
#include "Camera.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObjectRenderState::GameObjectRenderState(Camera* camera)
  : camera_(camera)
  , layer_state_(1)
  , view_proj_matrix_(Matrix4x4::identity)
  , world_matrix_(Matrix4x4::identity)
{
  for (T_UINT8 i = 0; i < GraphicsConstants::RQ_DATANUM; ++i)
  {
    this->queues_[i] = new GameObjectRenderQueue();
  }
}

GameObjectRenderState::~GameObjectRenderState()
{
  for (T_UINT8 i = 0; i < GraphicsConstants::RQ_DATANUM; ++i)
  {
    delete this->queues_[i];
  }
}

// =================================================================
// Method
// =================================================================
void GameObjectRenderState::Init()
{
  this->view_proj_matrix_ = this->camera_->GetViewMatrix();
  this->view_proj_matrix_ *= this->camera_->GetProjectionMatrix();
}

void GameObjectRenderState::Draw()
{
  using namespace GraphicsConstants;
  for (T_UINT8 i = RQ_GEOMETRY_BEGIN; i < RQ_GEOMETRY_LAST; ++i)
  {
    queues_[i]->Draw(this);
  }
  for (T_UINT8 i = RQ_TRANSPARENT; i < RQ_DATANUM; ++i)
  {
    queues_[i]->DrawWithZSorted(this);
  }
}

void GameObjectRenderState::AddQueue(const Renderer* renderer)
{
  using namespace GraphicsConstants;
  RenderQueue queue = renderer->GetMaterial()->GetRenderQueue();
  if (queue < RQ_GEOMETRY_LAST)
  {
    this->queues_[queue]->Add(renderer);
    return;
  }
  this->queues_[queue]->AddByDistance(renderer, this->camera_);
}
