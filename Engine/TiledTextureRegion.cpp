#include "TiledTextureRegion.h"
#include "Util.h"
#include "Director.h"
#include "HalEngine.h"

// =================================================================
// Factory Method
// =================================================================
TiledTextureRegion* TiledTextureRegion::CreateWithTexture(const ITexture* texture, T_UINT8 x_num, T_UINT8 y_num)
{
  TiledTextureRegion* ret = new TiledTextureRegion();
  ret->Init();
  ret->SetTexture(texture);
  ret->SetXNum(x_num);
  ret->SetYNum(y_num);
  ret->FitToTexture();
  return ret;
}

TiledTextureRegion* TiledTextureRegion::CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id, T_UINT8 x_num, T_UINT8 y_num)
{
  const ITexture* texture = HalEngine::Resource::GetTexture(palette_id, texture_id);
  return TiledTextureRegion::CreateWithTexture(texture, x_num, y_num);
}

// =================================================================
// Constructor / Destructor
// =================================================================
TiledTextureRegion::TiledTextureRegion()
  : x_num_(1)
  , y_num_(1)
  , current_index_(0)
  , format_(TTR_FORMAT_LOOP)
{}

TiledTextureRegion::~TiledTextureRegion()
{
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void TiledTextureRegion::OnUpdateTextureCoord()
{
  const TSize texture_size = this->GetTexture()->GetSize();
  const T_FLOAT region_x = this->GetX();
  const T_FLOAT region_y = this->GetY();
  const T_FLOAT region_w = this->GetWidth();
  const T_FLOAT region_h = this->GetHeight();
  const T_UINT16 current_index = this->CalcCurrentIndex();
  const T_UINT8 x = current_index % this->x_num_;
  const T_UINT8 y = (current_index / this->x_num_) % this->y_num_;
  const T_FLOAT w = 1.0f / this->x_num_;
  const T_FLOAT h = 1.0f / this->y_num_;
  const T_FLOAT rateX = region_w / texture_size.width;
  const T_FLOAT rateY = region_h / texture_size.height;
  this->SetU0(region_x + (x * w) * rateX);
  this->SetV0(region_y + (y * h) * rateY);
  this->SetU1(region_x + (x * w + w) * rateX);
  this->SetV1(region_y + (y * h + h) * rateY);
}

T_UINT16 TiledTextureRegion::CalcCurrentIndex()
{
  const T_UINT16 ret = this->current_index_;
  const T_UINT16 min = 0;
  const T_UINT16 max = this->x_num_ * this->y_num_;
  if (min == max)
  {
    return 0;
  }
  if (this->format_ == TTR_FORMAT_CLAMP)
  {
    return Util::Clamp(ret, min, max);
  }
  if (this->format_ == TTR_FORMAT_LOOP)
  {
    return ret % max;
  }
  if (this->format_ == TTR_FORMAT_NONE)
  {
    return ret;
  }
  return 0;
}

// =================================================================
// setter/getter
// =================================================================
void TiledTextureRegion::SetXNum(T_UINT8 x_num)
{
  if (this->x_num_ == x_num)
  {
    return;
  }
  this->x_num_ = x_num;
  this->OnTextureCoordDirty();
}

void TiledTextureRegion::SetYNum(T_UINT8 y_num)
{
  if (this->y_num_ == y_num)
  {
    return;
  }
  this->y_num_ = y_num;
  this->OnTextureCoordDirty();
}

void TiledTextureRegion::SetCurrentIndex(T_UINT16 current_index)
{
  if (this->current_index_ == current_index)
  {
    return;
  }
  this->current_index_ = current_index;
  this->OnTextureCoordDirty();
}

void TiledTextureRegion::SetTiledTextureRegionFormat(TiledTextureRegionFormat format)
{
  if (this->format_ == format)
  {
    return;
  }
  this->format_ = format;
  this->OnTextureCoordDirty();
}
