#include "TextureRegion.h"
#include <stdlib.h>
#include "Moniker.h"

// =================================================================
// Factory Method
// =================================================================
TextureRegion* TextureRegion::CreateWithTexture(const Texture* texture)
{
  TextureRegion* ret = new TextureRegion();
  ret->Init();
  ret->SetTexture(texture);
  ret->FitToTexture();
  return ret;
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
void TextureRegion::OnUpdateTextureCoord(const Texture* texture)
{
  const T_FLOAT tw = (T_FLOAT)texture->GetWidth();
  const T_FLOAT th = (T_FLOAT)texture->GetHeight();
  const T_FLOAT x = this->GetX();
  const T_FLOAT y = this->GetY();
  const T_FLOAT w = this->GetWidth();
  const T_FLOAT h = this->GetHeight();
  this->SetU0(x / tw);
  this->SetV0(y / th);
  this->SetU1((x + w) / tw);
  this->SetV1((y + h) / th);
}