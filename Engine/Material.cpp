#include "Material.h"
#include "GameObjectRenderState.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Material::Material(const ShaderResource& resource, bool protect)
  : protected_(protect)
  , shader_resource_(&resource)
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

// =================================================================
// Method
// =================================================================
Material* Material::Clone()
{
  Material* ret = new Material(*this->shader_resource_);
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
  NATIVE_ASSERT(this->shader_resource_, "シェーダーが未定義です");
  Material* ret = new Material(*this->shader_resource_);
  this->clones_.push_back(ret);
  return ret;
}

void Material::Begin(GameObjectRenderState* state)
{
  INativeShader* shader = this->GetShader();
  shader->Begin();
  for (auto pair : this->properties_)
  {
    pair.second->Apply(shader, pair.first);
  }
}

void Material::CommitChanges(GameObjectRenderState* state)
{
  INativeShader* shader = this->GetShader();
  NativeTextureInstance* texture = this->texture_ ? this->texture_->GetContents()->GetNativeInstance() : nullptr;
  shader->SetTexture("_MainTex", texture);
  shader->SetColor("_Diffuse", this->color_);
  shader->SetMatrix("_WorldViewProj", state->GetWorldViewProjToMaterial()->GetNativeInstance());
  shader->CommitChanges();
}

void Material::End()
{
  this->GetShader()->End();
}