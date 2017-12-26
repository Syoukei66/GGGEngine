#include "AnimatedSprite3D.h"
#include "TiledTextureRegion.h"
#include "HalEngine.h"

AnimatedSprite3D* AnimatedSprite3D::CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id, T_UINT8 x_num, T_UINT8 y_num)
{
  AnimatedSprite3D* ret = new AnimatedSprite3D();
  const ITexture* texture = HalEngine::Resource::GetTexture(palette_id, texture_id);
  TiledTextureRegion* region = TiledTextureRegion::CreateWithTexture(texture, x_num, y_num);
  ret->Init();
  ret->SetTextureRegion(region);
  ret->FitToTexture();
  return ret;
}

AnimatedSprite3D::AnimatedSprite3D()
  : frame_count_(0)
  , duration_frame_(0)
{}

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
      region->SetCurrentIndex(region->GetCurrentIndex() + 1);
    }
  }
  Sprite3D::Update();
}

void AnimatedSprite3D::Animate(T_UINT16 duration_frame)
{
  this->duration_frame_ = duration_frame;
}

void AnimatedSprite3D::SetCurrentIndex(T_UINT16 index)
{
  this->GetTiledTextureRegion()->SetCurrentIndex(index);
}

