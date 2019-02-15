#include "GameObjectRenderState.h"
#include "GameObject.h"

#include <Engine/Component/Camera/Camera.h>
#include <Engine/GameObject/GameObject.h>
#include <Engine/Component/Renderer/Renderer.h>

// =================================================================
// Constructor / Destructor
// =================================================================
GameObjectRenderState::GameObjectRenderState(Camera* camera)
  : camera_(camera)
  , layer_state_(1)
  , queues_()
  , builtin_variable_()
  , builtin_variable_buffer_()
{
  for (T_UINT8 i = 0; i < Graphics::RQ_DATANUM; ++i)
  {
    this->queues_[i] = new GameObjectRenderQueue();
  }
  this->builtin_variable_buffer_ = rcConstantBuffer::Create(Shader::ConstantBufferId::kRenderStateBuiltin, sizeof(ShaderBuiltinData));
}

GameObjectRenderState::~GameObjectRenderState()
{
  for (T_UINT8 i = 0; i < Graphics::RQ_DATANUM; ++i)
  {
    delete this->queues_[i];
  }
}

// =================================================================
// Methods
// =================================================================
void GameObjectRenderState::Init()
{
  // https://docs.unity3d.com/ja/2017.4/Manual/SL-UnityShaderVariables.html
  this->builtin_variable_.mat_v = this->camera_->GetViewMatrix();
  this->builtin_variable_.mat_p = this->camera_->GetProjectionMatrix();
  this->builtin_variable_.mat_vp = this->builtin_variable_.mat_v;
  this->builtin_variable_.mat_vp *= this->builtin_variable_.mat_p;

  this->builtin_variable_.world_space_camera_pos_ = TVec4f(this->camera_->GetTransform()->GetWorldPosition(), 0.0f);

  const T_FLOAT near = this->camera_->GetViewportZMin();
  const T_FLOAT far = this->camera_->GetViewportZMax();
  const T_FLOAT width = this->camera_->GetViewportWidth();
  const T_FLOAT height = this->camera_->GetViewportHeight();
  const T_FLOAT inv_near = 1.0f / near;
  const T_FLOAT inv_far = 1.0f / far;

  this->builtin_variable_.projection_params_.x = 1.0f;
  this->builtin_variable_.projection_params_.y = near;
  this->builtin_variable_.projection_params_.z = far;
  this->builtin_variable_.projection_params_.w = inv_far;

  this->builtin_variable_.screen_params_.x = width;
  this->builtin_variable_.screen_params_.y = height;
  this->builtin_variable_.screen_params_.z = 1.0f + 1.0f / width;
  this->builtin_variable_.screen_params_.w = 1.0f + 1.0f / height;

  this->builtin_variable_.z_buffer_params_.x = 1.0f - far * inv_near;
  this->builtin_variable_.z_buffer_params_.y = far * inv_near;
  this->builtin_variable_.z_buffer_params_.z = inv_far - inv_near; 
  this->builtin_variable_.z_buffer_params_.w = inv_near;

  this->builtin_variable_.ortho_params_.x = width;
  this->builtin_variable_.ortho_params_.y = height;
  this->builtin_variable_.ortho_params_.z = 0.0f;
  this->builtin_variable_.ortho_params_.w = 0.0f;

  this->builtin_variable_buffer_->CommitChanges(&this->builtin_variable_);
}

void GameObjectRenderState::Draw()
{
  using namespace Graphics;
  for (T_UINT8 i = RQ_GEOMETRY_BEGIN; i < RQ_GEOMETRY_LAST; ++i)
  {
    queues_[i]->Draw(this);
  }
  for (T_UINT8 i = RQ_GEOMETRY_LAST; i < RQ_TRANSPARENT_LAST; ++i)
  {
    queues_[i]->DrawTransparent(this);
  }
}

void GameObjectRenderState::AddQueue(const Renderer* renderer)
{
  using namespace Graphics;
  RenderQueue queue = renderer->GetMaterial()->GetShader()->GetRenderQueue();
  if (queue < RQ_GEOMETRY_LAST)
  {
    this->queues_[queue]->Add(renderer);
    return;
  }
  this->queues_[queue]->AddByDistance(renderer, this->camera_);
}
