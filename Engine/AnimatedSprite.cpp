#include "AnimatedSprite.h"
#include "EngineAsset.h"

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
  ret->SetAnimateRange(0, region->GetTileCount() - 1);
  ret->FitToTexture();
  return ret;
}

AnimatedSprite* AnimatedSprite::CreateWithMaterial(Material* material, T_UINT8 x_num, T_UINT8 y_num)
{
  TiledTextureRegion* region = TiledTextureRegion::CreateWithMaterial(material, x_num, y_num);
  AnimatedSprite* ret = AnimatedSprite::CreateWithTextureRegion(region);
  ret->SetMaterial(*material);
  ret->delete_region_ = true;
  return ret;
}

AnimatedSprite* AnimatedSprite::CreateWithTexture(const Texture* texture, T_UINT8 x_num, T_UINT8 y_num)
{
  Material* mat = EngineAsset::Material::SPRITE.Clone();
  mat->SetMainTexture(texture);
  return CreateWithMaterial(mat, x_num, y_num);
}

// =================================================================
// Constructor / Destructor
// =================================================================
AnimatedSprite::AnimatedSprite()
  : frame_count_(0)
  , duration_frame_(0)
  , animation_begin_(0)
  , animation_end_(0)
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
      this->SetCurrentIndex(region->GetCurrentIndex() + 1);
    }
  }
  Sprite::PreDraw(state);
}

// =================================================================
// Methods
// =================================================================
void AnimatedSprite::SetAnimateRange(T_UINT16 begin, T_UINT16 end)
{
  this->animation_begin_ = begin;
  this->animation_end_ = end;
  this->SetCurrentIndex(this->GetCurrentIndex());
}

void AnimatedSprite::Animate(T_UINT16 duration_frame)
{
  this->duration_frame_ = duration_frame;
}

// =================================================================
// Setter / Getter
// =================================================================
void AnimatedSprite::SetCurrentIndex(T_UINT16 index)
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