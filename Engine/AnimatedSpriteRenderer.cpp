#include "AnimatedSpriteRenderer.h"

// =================================================================
// Constructor / Destructor
// =================================================================
AnimatedSpriteRenderer::AnimatedSpriteRenderer(GameObject* entity, T_FLOAT image_scale)
  : SpriteRenderer(entity, image_scale)
  , frame_count_(0)
  , duration_frame_(0)
  , animation_begin_(0)
  , animation_end_(0)
{}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void AnimatedSpriteRenderer::Update()
{
  ++this->frame_count_;
  if (this->duration_frame_ == 0 || this->frame_count_ < this->duration_frame_)
  {
    return;
  }
  this->frame_count_ = 0;
  this->SetCurrentIndex(this->GetCurrentIndex() + 1);
}

// =================================================================
// setter/getter
// =================================================================
void AnimatedSpriteRenderer::SetAnimateRange(T_UINT16 begin, T_UINT16 end)
{
  this->animation_begin_ = begin;
  this->animation_end_ = end;
  this->SetCurrentIndex(this->GetCurrentIndex());
}

void AnimatedSpriteRenderer::Animate(T_UINT16 duration_frame)
{
  this->duration_frame_ = duration_frame;
}

void AnimatedSpriteRenderer::SetCurrentIndex(T_UINT16 index)
{
  TiledTextureRegion* region = (TiledTextureRegion*)this->GetTextureRegion();
  if (!region)
  {
    return;
  }
  const T_UINT16 state_count = this->animation_end_ - this->animation_begin_ + 1;
  const T_UINT16 local_loop = index / state_count;
  const T_UINT16 local_index = index % state_count;
  region->SetCurrentIndex(local_loop * region->GetTileCount() + this->animation_begin_ + local_index);
}
