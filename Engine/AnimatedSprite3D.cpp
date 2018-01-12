#include "AnimatedSprite3D.h"
#include "TiledTextureRegion.h"
#include "Moniker.h"

// =================================================================
// Factory Method
// =================================================================
AnimatedSprite3D* AnimatedSprite3D::CreateWithTexture(const Texture* texture, T_UINT8 x_num, T_UINT8 y_num)
{
  AnimatedSprite3D* ret = new AnimatedSprite3D();
  TiledTextureRegion* region = TiledTextureRegion::CreateWithTexture(texture, x_num, y_num);
  ret->Init();
  ret->SetTextureRegion(region);
  ret->SetAnimateRange(0, region->GetTileCount() - 1);
  ret->FitToTexture();
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
AnimatedSprite3D::AnimatedSprite3D()
  : frame_count_(0)
  , duration_frame_(0)
  , animation_begin_(0)
  , animation_end_(0)
{}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void AnimatedSprite3D::Init()
{
  Sprite3D::Init();
  this->frame_count_ = 0;
  this->duration_frame_ = 0;
}

void AnimatedSprite3D::Update()
{
  TiledTextureRegion* region = (TiledTextureRegion*)this->GetTextureRegion();
  if (this->duration_frame_ != 0)
  {
    this->frame_count_++;
    if (this->frame_count_ % this->duration_frame_ == 0 && region)
    {
      this->SetCurrentIndex(region->GetCurrentIndex() + 1);
    }
  }
  Sprite3D::Update();
}

// =================================================================
// Method
// =================================================================
void AnimatedSprite3D::SetAnimateRange(T_UINT16 begin, T_UINT16 end)
{
  this->animation_begin_ = begin;
  this->animation_end_ = end;
  this->SetCurrentIndex(this->GetCurrentIndex());
}

void AnimatedSprite3D::Animate(T_UINT16 duration_frame)
{
  this->duration_frame_ = duration_frame;
}

// =================================================================
// Setter / Getter
// =================================================================
void AnimatedSprite3D::SetCurrentIndex(T_UINT16 index)
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

