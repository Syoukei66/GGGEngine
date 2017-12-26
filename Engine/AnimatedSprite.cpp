#include "AnimatedSprite.h"

// =================================================================
// Factory Method
// =================================================================
AnimatedSprite* AnimatedSprite::Create()
{
  AnimatedSprite* ret = new AnimatedSprite();
  ret->Init();
  return ret;
}

AnimatedSprite* AnimatedSprite::CreateWithTextureRegion(TiledTextureRegion* region)
{
  AnimatedSprite* ret = AnimatedSprite::Create();
  ret->SetTextureRegion(region);
  ret->FitToTexture();
  return ret;
}

AnimatedSprite* AnimatedSprite::CreateWithTexture(const ITexture* texture, T_UINT8 x_num, T_UINT8 y_num)
{
  TiledTextureRegion* region = TiledTextureRegion::CreateWithTexture(texture, x_num, y_num);
  AnimatedSprite* ret = AnimatedSprite::CreateWithTextureRegion(region);
  ret->delete_region_ = true;
  return ret;
}

AnimatedSprite* AnimatedSprite::CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id, T_UINT8 x_num, T_UINT8 y_num)
{
  TiledTextureRegion* region = TiledTextureRegion::CreateFromAsset(palette_id, texture_id, x_num, y_num);
  AnimatedSprite* ret = AnimatedSprite::CreateWithTextureRegion(region);
  ret->delete_region_ = true;
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
AnimatedSprite::AnimatedSprite()
  : frame_count_(0)
  , duration_frame_(0)
{}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void AnimatedSprite::Init()
{
  Sprite::Init();
  this->frame_count_ = 0;
  this->duration_frame_ = 0;
}

void AnimatedSprite::PreDraw(GameObject2DRenderState* state)
{
  TiledTextureRegion* region = (TiledTextureRegion*)this->GetTextureRegion();
  if (this->duration_frame_ != 0)
  {
    this->frame_count_++;
    if (this->frame_count_ % this->duration_frame_ == 0 && region)
    {
      region->SetCurrentIndex(region->GetCurrentIndex() + 1);
    }
  }
  Sprite::PreDraw(state);
}

// =================================================================
// Methods
// =================================================================
void AnimatedSprite::Animate(T_UINT16 duration_frame)
{
  this->duration_frame_ = duration_frame;
}

// =================================================================
// Setter / Getter
// =================================================================
void AnimatedSprite::SetCurrentIndex(T_UINT16 index)
{
  this->GetTiledTextureRegion()->SetCurrentIndex(index);
}