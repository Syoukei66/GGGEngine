#include "Material.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Material::Material(INativeShader* resource, bool protect)
  : protected_(protect)
  , shader_resource_(resource)
  , technique_("Default")
  , queue_(Graphics::RenderQueue::RQ_GEOMETRY)
{
}

Material::~Material()
{
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
  NATIVE_ASSERT(this->shader_resource_, "シェーダーが未定義です");
  Material* ret = this->CreateClone(this->shader_resource_);
  this->clones_.emplace_back(ret);
  return ret;
}

Material* Material::CreateClone(INativeShader* shader)
{
  return new Material(shader);
}

void Material::CopyPropertiesToClone(Material* clone)
{
}


T_UINT8 Material::Begin()
{
  this->shader_resource_->SetTechnique(this->technique_);
  return this->shader_resource_->Begin();
}

void Material::BeginPass(T_UINT8 path_id)
{
  INativeShader* shader = this->shader_resource_;
  shader->BeginPass(path_id);
  if (path_id > 0)
  {
    return;
  }
}

void Material::CommitChanges()
{
  this->shader_resource_->CommitChanges();
}

void Material::EndPass()
{
  this->shader_resource_->EndPass();
}

void Material::End()
{
  this->shader_resource_->End();
}