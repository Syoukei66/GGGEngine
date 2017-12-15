#include "LoopTextureRegion.h"
#include "HalEngine.h"

// =================================================================
// Factory Method
// =================================================================
LoopTextureRegion* LoopTextureRegion::CreateWithTexture(const ITexture* texture)
{
  LoopTextureRegion* ret = new LoopTextureRegion();
  ret->Init();
  ret->SetTexture(texture);
  ret->SetLoopWidth((T_FLOAT)texture->GetSize().width);
  ret->SetLoopHeight((T_FLOAT)texture->GetSize().height);
  ret->FitToTexture();
  return ret;
}

LoopTextureRegion* LoopTextureRegion::CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id)
{
  const ITexture* texture = HalEngine::Resource::GetTexture(palette_id, texture_id);
  return LoopTextureRegion::CreateWithTexture(texture);
}

// =================================================================
// Constructor / Destructor
// =================================================================
LoopTextureRegion::LoopTextureRegion()
  : loop_size_(1.0f, 1.0f)
  , loop_offset_(0.0f, 0.0f)
{}

LoopTextureRegion::~LoopTextureRegion()
{}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void LoopTextureRegion::OnUpdateTextureCoord()
{
  const TSize texture_size = this->GetTexture()->GetSize();
  const T_FLOAT region_w = this->GetWidth();
  const T_FLOAT region_h = this->GetHeight();
  const T_FLOAT loop_w = this->GetLoopWidth();
  const T_FLOAT loop_h = this->GetLoopHeight();
  const T_FLOAT x = this->GetLoopOffsetX();
  const T_FLOAT y = this->GetLoopOffsetY();
  const T_FLOAT w = loop_w / region_w;
  const T_FLOAT h = loop_h / region_h;
  this->SetU0(x);
  this->SetV0(y);
  this->SetU1(x + w);
  this->SetV1(y + h);
}

// =================================================================
// setter/getter
// =================================================================
void LoopTextureRegion::SetLoopSize(const TSizef& size)
{
  if (this->loop_size_ == size)
  {
    return;
  }
  this->loop_size_ = size;
  this->OnTextureCoordDirty();
}

void LoopTextureRegion::SetLoopWidth(T_FLOAT width)
{
  if (this->loop_size_.width == width)
  {
    return;
  }
  this->loop_size_.width = width;
  this->OnTextureCoordDirty();
}

void LoopTextureRegion::SetLoopHeight(T_FLOAT height)
{
  if (this->loop_size_.height == height)
  {
    return;
  }
  this->loop_size_.height = height;
  this->OnTextureCoordDirty();
}

void LoopTextureRegion::SetLoopOffset(const TVec2f& offset)
{
  if (this->loop_offset_ == offset)
  {
    return;
  }
  this->loop_offset_ = offset;
  this->OnTextureCoordDirty();
}

void LoopTextureRegion::SetLoopOffsetX(T_FLOAT x)
{
  if (this->loop_offset_.x == x)
  {
    return;
  }
  this->loop_offset_.x = x;
  this->OnTextureCoordDirty();
}

void LoopTextureRegion::SetLoopOffsetY(T_FLOAT y)
{
  if (this->loop_offset_.y == y)
  {
    return;
  }
  this->loop_offset_.y = y;
  this->OnTextureCoordDirty();
}
