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

Sprite* Sprite::CreateWithTexture(const Texture* texture)
{
  TextureRegion* region = TextureRegion::CreateWithTexture(texture);
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
  const Texture* texture = this->texture_region_->GetTexture();
  if (this->texture_region_->UpdateTextureCoord())
  {
    this->vbo_->OnVertexUvDirty();
  }
  this->vbo_->UpdateTexture(this, this->texture_region_);
}

void Sprite::NativeDraw(GameObject2DRenderState* state)
{
  //if (!this->texture_region_)
  //{
  //  return;
  //}
  //const Texture* texture = this->texture_region_->GetTexture();
  //if (!texture)
  //{
  //  return;
  //}
  NativeMethod::Graphics().Graphics_DrawSprite(
    state,
    INativeProcess_Graphics::PRIMITIVE_TRIANGLESTRIP,
    (SpriteVertex*)this->vbo_->GetVertexes(),
    this->vbo_->GetVertexesCount()
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
  const Texture* texture = this->texture_region_->GetTexture();
  if (!texture)
  {
    return;
  }
  T_FLOAT tw = (T_FLOAT)texture->GetWidth();
  T_FLOAT th = (T_FLOAT)texture->GetHeight();
  this->SetWidth(tw * (this->texture_region_->GetU1() - this->texture_region_->GetU0()));
  this->SetHeight(th * (this->texture_region_->GetV1() - this->texture_region_->GetV0()));
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
