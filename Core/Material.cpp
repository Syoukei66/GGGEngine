#include "Material.h"

// =================================================================
// Constructor / Destructor
// =================================================================
rcMaterial::rcMaterial(rcShader* shader, bool protect)
  : protected_(protect)
  , shader_(shader)
  , technique_("Default")
  , queue_(Graphics::RenderQueue::RQ_GEOMETRY)
{
  this->shader_->Retain();
}

rcMaterial::~rcMaterial()
{
  this->shader_->Release();
  for (rcMaterial* clone : this->clones_)
  {
    delete clone;
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
  this->CopyPropertiesToClone(ret);

  return ret;
}

rcMaterial* rcMaterial::InitialClone()
{
  NATIVE_ASSERT(this->shader_, "シェーダーが未定義です");
  rcMaterial* ret = this->CreateClone(this->shader_);
  this->clones_.emplace_back(ret);
  return ret;
}

rcMaterial* rcMaterial::CreateClone(rcShader* shader)
{
  return new rcMaterial(shader);
}

void rcMaterial::CopyPropertiesToClone(rcMaterial* clone)
{
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
