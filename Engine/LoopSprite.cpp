#include "LoopSprite.h"

// =================================================================
// Factory Method
// =================================================================
LoopSprite* LoopSprite::Create()
{
  LoopSprite* ret = new LoopSprite();
  ret->Init();
  return ret;
}

LoopSprite* LoopSprite::CreateWithTextureRegion(LoopTextureRegion* region)
{
  LoopSprite* ret = LoopSprite::Create();
  ret->SetTextureRegion(region);
  ret->FitToTexture();
  return ret;
}

LoopSprite* LoopSprite::CreateWithTexture(const ITexture* texture)
{
  LoopTextureRegion* region = LoopTextureRegion::CreateWithTexture(texture);
  LoopSprite* ret = LoopSprite::CreateWithTextureRegion(region);
  ret->delete_region_ = true;
  return ret;
}

LoopSprite* LoopSprite::CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id)
{
  LoopTextureRegion* region = LoopTextureRegion::CreateFromAsset(palette_id, texture_id);
  LoopSprite* ret = LoopSprite::CreateWithTextureRegion(region);
  ret->delete_region_ = true;
  return ret;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void LoopSprite::OnVertexCoordChanged()
{
  Shape::OnVertexCoordChanged();
  LoopTextureRegion* region = this->GetLoopTextureRegion();
  region->SetLoopSize(this->GetSize());
}
