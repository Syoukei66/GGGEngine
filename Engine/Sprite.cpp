#include "Sprite.h"
#include "TextureRegion.h"
#include "NativeMethod.h"
#include "GameObject2DRenderState.h"
#include "EngineAsset.h"

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

Sprite* Sprite::CreateWithMaterial(Material* material)
{
  TextureRegion* region = TextureRegion::CreateWithTexture(material->GetMainTexture());
  Sprite* ret = Sprite::CreateWithTextureRegion(region);
  ret->SetMaterial(*material);
  ret->delete_region_ = true;
  return ret;
}

Sprite* Sprite::CreateWithTexture(const Texture* texture)
{
  Material* mat = EngineAsset::Material::SPRITE.Clone();
  mat->SetMainTexture(texture);
  return CreateWithMaterial(mat);
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
  this->SetMaterial(EngineAsset::Material::SPRITE);
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
  NativeMethod::Graphics().Graphics_DrawSprite(
    state,
    INativeProcess_Graphics::PRIMITIVE_TRIANGLESTRIP,
    (SpriteVertex*)this->vbo_->GetVertexes(),
    this->vbo_->GetVertexesCount()
  );
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
  T_FLOAT tw = texture_region_->GetWidth();
  T_FLOAT th = texture_region_->GetHeight();
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
