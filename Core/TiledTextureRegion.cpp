#include "TiledTextureRegion.h"
#include "Mathf.h"

// =================================================================
// Factory Method
// =================================================================
UniqueResource<rcTiledTextureRegion> rcTiledTextureRegion::CreateWithMaterial(const SharedRef<const rcMaterial>& material, T_UINT8 x_num, T_UINT8 y_num)
{
  return rcTiledTextureRegion::CreateWithTexture(material->GetMainTexture(), x_num, y_num);
}

UniqueResource<rcTiledTextureRegion> rcTiledTextureRegion::CreateWithTexture(const SharedRef<const rcTexture>& texture, T_UINT8 x_num, T_UINT8 y_num)
{
  UniqueResource<rcTiledTextureRegion> ret = rcTiledTextureRegion::Create();
  ret->Init();
  ret->SetTexture(texture);
  ret->SetXNum(x_num);
  ret->SetYNum(y_num);
  ret->FitToTexture();
  return ret;
}

UniqueResource<rcTiledTextureRegion> rcTiledTextureRegion::Create()
{
  rcTiledTextureRegion* ret = new rcTiledTextureRegion();
  ret->Resource::Init();
  return UniqueResource<rcTiledTextureRegion>(ret);
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcTiledTextureRegion::rcTiledTextureRegion()
  : x_num_(1)
  , y_num_(1)
  , current_index_(0)
  , format_(TTR_FORMAT_LOOP)
{}

rcTiledTextureRegion::~rcTiledTextureRegion()
{
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void rcTiledTextureRegion::OnUpdateTextureCoord(const SharedRef<const rcTexture>& texture)
{
  const T_FLOAT tw = (T_FLOAT)texture->GetWidth();
  const T_FLOAT th = (T_FLOAT)texture->GetHeight();
  const T_FLOAT region_x = this->GetX();
  const T_FLOAT region_y = this->GetY();
  const T_FLOAT region_w = this->GetWidth();
  const T_FLOAT region_h = this->GetHeight();
  const T_UINT16 current_index = this->CalcCurrentIndex();
  const T_UINT8 x = current_index % this->x_num_;
  const T_UINT8 y = (current_index / this->x_num_) % this->y_num_;
  const T_FLOAT w = 1.0f / this->x_num_;
  const T_FLOAT h = 1.0f / this->y_num_;
  const T_FLOAT rateX = region_w / tw;
  const T_FLOAT rateY = region_h / th;
  this->SetU0(region_x + (x * w) * rateX);
  this->SetV0(region_y + (y * h) * rateY);
  this->SetU1(region_x + (x * w + w) * rateX);
  this->SetV1(region_y + (y * h + h) * rateY);
}

T_UINT16 rcTiledTextureRegion::CalcCurrentIndex()
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
    return Mathf::Clamp(ret, min, max);
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
void rcTiledTextureRegion::SetXNum(T_UINT8 x_num)
{
  if (this->x_num_ == x_num)
  {
    return;
  }
  this->x_num_ = x_num;
  this->OnTextureCoordDirty();
}

void rcTiledTextureRegion::SetYNum(T_UINT8 y_num)
{
  if (this->y_num_ == y_num)
  {
    return;
  }
  this->y_num_ = y_num;
  this->OnTextureCoordDirty();
}

void rcTiledTextureRegion::SetCurrentIndex(T_UINT16 current_index)
{
  if (this->current_index_ == current_index)
  {
    return;
  }
  this->current_index_ = current_index;
  this->OnTextureCoordDirty();
}

void rcTiledTextureRegion::SetTiledTextureRegionFormat(TiledTextureRegionFormat format)
{
  if (this->format_ == format)
  {
    return;
  }
  this->format_ = format;
  this->OnTextureCoordDirty();
}
