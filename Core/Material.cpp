#include "Material.h"
#include "AssetManager.h"

// =================================================================
// Factory Method
// =================================================================
rcMaterial* rcMaterial::CreateFromFile(const char* path)
{
  return rcMaterial::Create(MaterialData::Deserialize(path));
}

rcMaterial* rcMaterial::Create(rcShader* resource)
{
  rcMaterial* ret = new rcMaterial(resource);
  ret->Resource::Init();
  return ret;
}

//デフォルトアセットの登録ができていない(というかそもそもやってなかった)

rcMaterial* rcMaterial::Create(const MaterialData* data)
{
  rcShader* resource = AssetManager::GetLoader<rcShader>(data->shader_unique_id_)->CreateFromFile();
  rcMaterial* ret = new rcMaterial(resource);
  ret->texture_ = AssetManager::GetLoader<rcTexture>(data->main_tex_unique_id_)->CreateFromFile();
  ret->tiling_ = data->tiling_;
  ret->tiling_offset_ = data->tiling_offset_;
  ret->color_ = data->color_;
  ret->billbording_ = data->billbording_;

  for (const auto& pair : data->texture_properties_)
  {
    ret->TextureProperty(pair.first) = AssetManager::GetLoader<rcTexture>(pair.second)->CreateFromFile();
  }

  for (const auto& pair : data->properties_)
  {
    ret->properties_[pair.first] = pair.second->Clone();
  }
  ret->Resource::Init();
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcMaterial::rcMaterial(rcShader* shader)
  : shader_(shader)
  , technique_("Default")
  , queue_(Graphics::RenderQueue::RQ_GEOMETRY)
  , properties_()
  , texture_()
  , tiling_()
  , tiling_offset_()
  , color_()
  , billbording_()
{
  this->shader_->Retain();
}

rcMaterial::~rcMaterial()
{
  this->shader_->Release();
  for (auto pair : this->properties_)
  {
    delete pair.second;
  }
}

// =================================================================
// Methods
// =================================================================
rcMaterial* rcMaterial::Clone() const
{
  rcMaterial* ret = this->InitialClone();
 
  ret->queue_ = this->queue_;
  ret->texture_ = this->texture_;
  for (auto pair : this->properties_)
  {
    ret->properties_[pair.first] = pair.second->Clone();
  }

  return ret;
}

rcMaterial* rcMaterial::InitialClone() const
{
  NATIVE_ASSERT(this->shader_, "シェーダーが未定義です");
  return new rcMaterial(this->shader_);
}

void rcMaterial::SetProperties(rcShader* shader) const
{
  shader->SetTechnique(this->technique_);
  for (auto pair : this->properties_)
  {
    pair.second->Apply(shader, pair.first);
  }
}

// =================================================================
// setter/getter
// =================================================================
void rcMaterial::SetShader(rcShader* shader)
{
  shader->Retain();
  if (this->shader_)
  {
    this->shader_->Release();
  }
  this->shader_ = shader;
}

void rcMaterial::SetMainTexture(const rcTexture* texture)
{
  texture->Retain();
  if (this->texture_)
  {
    this->texture_->Release();
  }
  this->texture_ = texture;
}
