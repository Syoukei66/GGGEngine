#include "TextureRegion.h"
#include <stdlib.h>
#include "ResourceManager.h"
#include "HalEngine.h"

// =================================================================
// Factory Method
// =================================================================
TextureRegion* TextureRegion::CreateWithTexture(const ITexture* texture)
{
  TextureRegion* ret = new TextureRegion();
  ret->Init();
  TSize size = texture->GetSize();
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
  const TSize texture_size = this->GetTexture()->GetSize();
  const T_FLOAT x = this->GetX();
  const T_FLOAT y = this->GetY();
  const T_FLOAT width = this->GetWidth();
  const T_FLOAT height = this->GetHeight();
  this->SetU0(x / texture_size.width);
  this->SetV0(y / texture_size.height);
  this->SetU1((x + width) / texture_size.width);
  this->SetV1((y + height) / texture_size.height);
}