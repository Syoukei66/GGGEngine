#include "RenderState.h"

#include "NativeProcess.h"
#include "GameObject.h"
#include "Camera.h"

// =================================================================
// Constructor / Destructor
// =================================================================
RenderState::RenderState()
  : layer_state_(1)
  , world_matrix_(Matrix4x4::identity)
  , view_matrix_(Matrix4x4::identity)
  , projection_matrix_(Matrix4x4::identity)
{
  for (T_UINT8 i = 0; i < Graphics::RQ_DATANUM; ++i)
  {
    this->queues_[i] = new RenderQueue();
  }
}

RenderState::~RenderState()
{
  for (T_UINT8 i = 0; i < Graphics::RQ_DATANUM; ++i)
  {
    delete this->queues_[i];
  }
}

// =================================================================
// Method
// =================================================================
void RenderState::Init()
{
  this->world_matrix_ = Matrix4x4::identity;
  this->view_matrix_ = Matrix4x4::identity;
  this->projection_matrix_ = Matrix4x4::identity;
}

void RenderState::Draw()
{
  using namespace Graphics;

  NativeProcess::Graphics::SetViewport(this->viewport_);
  if (this->color_buffer_ && this->depth_stencil_buffer_)
  {
    NativeProcess::Graphics::SetRenderTarget(this->color_buffer_, this->depth_stencil_buffer_, this->clear_flag_);
  }
  if (this->clear_flag_)
  {
    NativeProcess::Graphics::ViewportClear();
  }
  for (T_UINT8 i = RQ_GEOMETRY_BEGIN; i < RQ_GEOMETRY_LAST; ++i)
  {
    queues_[i]->Draw(this);
  }
  for (T_UINT8 i = RQ_TRANSPARENT; i < RQ_DATANUM; ++i)
  {
    queues_[i]->DrawWithZSorted(this);
  }

  if (this->color_buffer_ && this->depth_stencil_buffer_)
  {
    NativeProcess::Graphics::ResetRenderTarget();
  }
}

/*
  Renderer
  
*/

void RenderState::AddRenderer(const Renderer* renderer)
{
  using namespace Graphics;
  RenderQueue queue = renderer->GetMaterial()->GetRenderQueue();
  //if (queue < RQ_GEOMETRY_LAST)
  //{
  //  this->queues_[queue]->Add(renderer);
  //  return;
  //}
  this->queues_[queue]->AddByDistance(renderer, this->camera_);
}

void RenderState::AddRenderers(std::vector<Renderer*>::iterator& begin, std::vector<Renderer*>::iterator& end)
{
}

void RenderState::RemoveRenderer(const Renderer* renderer)
{
}

void RenderState::RemoveRenderers(std::vector<Renderer*>::iterator& begin, std::vector<Renderer*>::iterator& end)
{
}
