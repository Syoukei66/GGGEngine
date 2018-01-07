#include "TextureRegion.h"
#include <stdlib.h>
#include "ResourceManager.h"
#include "Moniker.h"

// =================================================================
// Factory Method
// =================================================================
TextureRegion* TextureRegion::CreateWithTexture(const ITexture* texture)
{
  TextureRegion* ret = new TextureRegion();
  ret->Init();
  ret->SetTexture(texture);
  ret->FitToTexture();
  return ret;
}

TextureRegion* TextureRegion::CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id)
{
  const ITexture* texture = HalEngine::Resource::GetTexture(palette_id, texture_id);
  return TextureRegion::CreateWithTexture(texture);
}

// =================================================================
// Constructor / Destructor
// =================================================================
TextureRegion::TextureRegion()
{}

TextureRegion::~TextureRegion()
{}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void TextureRegion::OnUpdateTextureCoord()
{
  const T_FLOAT tw = (T_FLOAT)this->GetTexture()->GetWidth();
  const T_FLOAT th = (T_FLOAT)this->GetTexture()->GetHeight();
  const T_FLOAT x = this->GetX();
  const T_FLOAT y = this->GetY();
  const T_FLOAT w = this->GetWidth();
  const T_FLOAT h = this->GetHeight();
  this->SetU0(x / tw);
  this->SetV0(y / th);
  this->SetU1((x + w) / tw);
  this->SetV1((y + h) / th);
}