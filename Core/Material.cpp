#include "Material.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Material::Material(rcShader* shader, bool protect)
  : protected_(protect)
  , shader_(shader)
  , technique_("Default")
  , queue_(Graphics::RenderQueue::RQ_GEOMETRY)
{
  this->shader_->Retain();
}

Material::~Material()
{
  this->shader_->Release();
  for (Material* clone : this->clones_)
  {
    delete clone;
  }
}

// =================================================================
// Methods
// =================================================================
Material* Material::Clone()
{
  Material* ret = this->InitialClone();
 
  ret->queue_ = this->queue_;
  ret->texture_ = this->texture_;
  this->CopyPropertiesToClone(ret);

  return ret;
}

Material* Material::InitialClone()
{
  NATIVE_ASSERT(this->shader_, "シェーダーが未定義です");
  Material* ret = this->CreateClone(this->shader_);
  this->clones_.emplace_back(ret);
  return ret;
}

Material* Material::CreateClone(rcShader* shader)
{
  return new Material(shader);
}

void Material::CopyPropertiesToClone(Material* clone)
{
}

T_UINT8 Material::Begin()
{
  this->shader_->SetTechnique(this->technique_);
  return this->shader_->Begin();
}

void Material::BeginPass(T_UINT8 path_id)
{
  rcShader* shader = this->shader_;
  shader->BeginPass(path_id);
  if (path_id > 0)
  {
    return;
  }
}

void Material::CommitChanges()
{
  this->shader_->CommitChanges();
}

void Material::EndPass()
{
  this->shader_->EndPass();
}

void Material::End()
{
  this->shader_->End();
}

// =================================================================
// setter/getter
// =================================================================
inline void Material::SetShader(rcShader* shader)
{
  if (this->shader_)
  {
    this->shader_->Release();
  }
  this->shader_ = shader;
  this->shader_->Retain();
}
