#include "Sprite.h"
#include "TextureRegion.h"
#include "NativeMethod.h"
#include "GameObject2DRenderState.h"
#include "EngineAsset.h"
#include "MeshRenderer.h"
#include "MeshData_Sprite.h"

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
  ret->GetRenderer()->SetMaterial(*material);
  ret->delete_region_ = true;
  return ret;
}

Sprite* Sprite::CreateWithTexture(const Texture& texture)
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
  this->renderer_ = new MeshRenderer();
  this->renderer_->AddMaterial(EngineAsset::Material::SPRITE);
  this->renderer_->SetMesh(Mesh::CreateWithMeshData(MeshData_Sprite::GetInstance()));
  this->SetRenderer(this->renderer_);
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void Sprite::Init()
{
  Shape::Init();
  this->texture_region_ = nullptr;
}

void Sprite::Update()
{
  Shape::Update();
  if (!this->texture_region_)
  {
    return;
  }
  this->texture_region_->UpdateTextureCoord();
  this->texture_region_->GetWidth();
  this->texture_region_->GetHeight();
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
  T_FLOAT tw = texture_region_->GetTexture()->GetWidth();
  T_FLOAT th = texture_region_->GetTexture()->GetHeight();
  this->SetWidth(tw * (this->texture_region_->GetU1() - this->texture_region_->GetU0()));
  this->SetHeight(th * (this->texture_region_->GetV1() - this->texture_region_->GetV0()));
}

// =================================================================
// setter/getter
// =================================================================
void Sprite::SetTextureRegion(ITextureRegion* itr)
{
  if (this->texture_region_ == itr)
  {
    return;
  }
  this->texture_region_ = itr;
  this->OnTextureChanged();
}
