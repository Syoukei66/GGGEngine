#include "Material.h"
#include "GameObjectRenderState.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Material::Material(const ShaderResource& resource)
  : shader_resource_(&resource)
  , shader_(nullptr)
  , properties_()
  , color_()
  , texture_()
  , z_test_(false)
{
}

Material::Material(INativeShader* shader)
  : shader_resource_(nullptr)
  , shader_(shader)
  , properties_()
  , color_()
  , texture_()
  , z_test_(false)
{
}

Material::~Material()
{
  for (auto pair : this->properties_)
  {
    delete pair.second;
  }
  for (Material* clone : this->clones_)
  {
    delete clone;
  }
}

Material* Material::Clone()
{
  Material* ret = new Material(this->shader_);
  for (auto pair : this->properties_)
  {
    ret->properties_[pair.first] = pair.second->Clone();
  }
  ret->color_ = this->color_;
  ret->texture_ = this->texture_;
  ret->z_test_ = this->z_test_;
  this->clones_.push_back(ret);
  return ret;
}

Material* Material::InitialClone()
{
  if (!this->shader_)
  {
    NATIVE_ASSERT(this->shader_resource_, "シェーダーが未定義です");
    this->shader_ = this->shader_resource_->GetContents();
  }
  Material* ret = new Material(this->shader_);
  this->clones_.push_back(ret);
  return ret;
}

// =================================================================
// Method
// =================================================================
void Material::Begin(GameObjectRenderState* state)
{
  if (!this->shader_)
  {
    NATIVE_ASSERT(this->shader_resource_, "シェーダーが未定義です");
    this->shader_ = this->shader_resource_->GetContents();
  }
  this->shader_->Begin();
  for (auto pair : this->properties_)
  {
    pair.second->Apply(this->shader_, pair.first);
  }
}

void Material::CommitChanges(GameObjectRenderState* state)
{
  NativeTextureInstance* texture = this->texture_ ? this->texture_->GetContents()->GetNativeInstance() : nullptr;
  this->shader_->SetTexture("_MainTex", texture);
  this->shader_->SetColor("_Diffuse", this->color_);
  this->shader_->SetMatrix("_WorldViewProj", state->GetWorldViewProjToMaterial()->GetNativeInstance());
  this->shader_->CommitChanges();
}

void Material::End()
{
  this->shader_->End();
}