#include "Sprite.h"
#include "TextureRegion.h"
#include "NativeMethod.h"
#include "GameObject2DRenderState.h"

// =================================================================
// Factory Method
// =================================================================
Sprite* Sprite::Create()
{
  Sprite* ret = new Sprite();
  ret->Init();
  return ret;
}

Sprite* Sprite::CreateWithTextureRegion(ITextureRegion* region)
{
  Sprite* ret = Sprite::Create();
  ret->SetTextureRegion(region);
  ret->FitToTexture();
  return ret;
}

Sprite* Sprite::CreateWithTexture(const ITexture* texture)
{
  TextureRegion* region = TextureRegion::CreateWithTexture(texture);
  Sprite* ret = Sprite::CreateWithTextureRegion(region);
  ret->delete_region_ = true;
  return ret;
}

Sprite* Sprite::CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id)
{
  TextureRegion* region = TextureRegion::CreateFromAsset(palette_id, texture_id);
  Sprite* ret = Sprite::CreateWithTextureRegion(region);
  ret->delete_region_ = true;
  return ret;
}
// =================================================================
// Constructor / Destructor
// =================================================================
Sprite::~Sprite()
{
  if (this->delete_region_ && this->texture_region_)
  {
    delete this->texture_region_;
  }
  if (this->vbo_)
  {
    delete this->vbo_;
  }
}

Sprite::Sprite()
{
  this->vbo_ = SpriteVertexBufferObject::Create();
  this->delete_region_ = false;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void Sprite::Init()
{
  Shape::Init();
  this->texture_region_ = nullptr;
}

void Sprite::PreDraw(GameObject2DRenderState* state)
{
  Shape::PreDraw(state);
  if (!this->texture_region_)
  {
    return;
  }
  const ITexture* texture = this->texture_region_->GetTexture();
  if (this->texture_region_->UpdateTextureCoord())
  {
    this->vbo_->OnVertexUvDirty();
  }
  this->vbo_->UpdateTexture(this, this->texture_region_);
}

void Sprite::NativeDraw(GameObject2DRenderState* state)
{
  if (!this->texture_region_)
  {
    return;
  }
  const ITexture* texture = this->texture_region_->GetTexture();
  if (!texture)
  {
    return;
  }
  T_UINT32 color = state->GetWorldPackedColor();
  SpriteVertex* vertexes = (SpriteVertex*)this->vbo_->GetVertexes();
  T_UINT32 size = this->vbo_->GetVertexesCount();
  for (T_UINT32 i = 0; i < size; ++i)
  {
    vertexes[i].packed_color = color;
  }
  NativeMethod::Graphics().Graphics_SetTexture(texture);
  NativeMethod::Graphics().Graphics_DrawSprite(
    state,
    INativeProcess_Graphics::PRIMITIVE_TRIANGLESTRIP,
    vertexes,
    size
  );
}

void Sprite::PostDraw(GameObject2DRenderState* state)
{
  Shape::PostDraw(state);
}

// =================================================================
// Method
// =================================================================
void Sprite::OnTextureChanged()
{
  this->vbo_->OnVertexUvDirty();
}

void Sprite::FitToTexture()
{
  if (!this->texture_region_)
  {
    return;
  }
  const ITexture* texture = this->texture_region_->GetTexture();
  if (!texture)
  {
    return;
  }
  TSize textureSize = texture->GetSize();
  this->SetWidth(textureSize.width * (this->texture_region_->GetU1() - this->texture_region_->GetU0()));
  this->SetHeight(textureSize.height * (this->texture_region_->GetV1() - this->texture_region_->GetV0()));
}

// =================================================================
// setter/getter
// =================================================================
IVertexBufferObject* Sprite::GetVbo() const
{
  return this->vbo_;
}

void Sprite::SetTextureRegion(ITextureRegion* itr)
{
  if (this->texture_region_ == itr)
  {
    return;
  }
  this->texture_region_ = itr;
  this->OnTextureChanged();
}
