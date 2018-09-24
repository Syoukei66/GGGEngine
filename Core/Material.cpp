#include "Material.h"
#include "AssetManager.h"
#include "ShaderAsset.h"
#include "TextureAsset.h"

// =================================================================
// Factory Method
// =================================================================
rcMaterial* rcMaterial::Create(rcShader* resource, bool protect)
{
  rcMaterial* ret = new rcMaterial(resource, protect);
  ret->Resource::Init();
  return ret;
}

rcMaterial* rcMaterial::Create(const MaterialData* data)
{
  rcShader* resource = AssetManager::GetInstance().GetAsset<ShaderAsset>(data->shader_unique_id_)->CreateFromFile();
  rcMaterial* ret = new rcMaterial(resource, data->protect_);
  ret->texture_ = AssetManager::GetInstance().GetAsset<TextureAsset>(data->main_tex_unique_id_)->CreateFromFile();
  ret->tiling_ = data->tiling_;
  ret->tiling_offset_ = data->tiling_offset_;
  ret->color_ = data->color_;
  ret->billbording_ = data->billbording_;

  for (const auto& pair : data->texture_properties_)
  {
    ret->TextureProperty(pair.first) = AssetManager::GetInstance().GetAsset<TextureAsset>(pair.second)->CreateFromFile();
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
rcMaterial::rcMaterial(rcShader* shader, bool protect)
  : protected_(protect)
  , shader_(shader)
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
rcMaterial* rcMaterial::Clone()
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

rcMaterial* rcMaterial::InitialClone()
{
  NATIVE_ASSERT(this->shader_, "シェーダーが未定義です");
  return new rcMaterial(this->shader_);
}

T_UINT8 rcMaterial::Begin()
{
  this->shader_->SetTechnique(this->technique_);
  return this->shader_->Begin();
}

void rcMaterial::BeginPass(T_UINT8 path_id)
{
  rcShader* shader = this->shader_;
  shader->BeginPass(path_id);
  if (path_id > 0)
  {
    return;
  }
}

void rcMaterial::CommitChanges()
{
  this->shader_->CommitChanges();
}

void rcMaterial::EndPass()
{
  this->shader_->EndPass();
}

void rcMaterial::End()
{
  this->shader_->End();
}

void rcMaterial::SetProperties(rcShader* shader)
{
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
  this->ProtectedAssertion();
  texture->Retain();
  if (this->texture_)
  {
    this->texture_->Release();
  }
  this->texture_ = texture;
}
