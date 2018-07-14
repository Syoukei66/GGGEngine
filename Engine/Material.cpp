#include "Material.h"
#include "RenderState.h"
#include "Camera.h"
#include "GameObject.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Material::Material(const ShaderResource& resource, bool protect)
  : protected_(protect)
  , shader_resource_(&resource)
  , properties_()
  , technique_("Default")
  , color_()
  , texture_()
  , clones_()
  , attribute_(Graphics::RenderAttribute::R_ATTR_GEOMETRY)
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
  ret->attribute_ = this->attribute_;
  this->clones_.emplace_back(ret);
  return ret;
}

Material* Material::InitialClone()
{
  NATIVE_ASSERT(this->shader_resource_, "シェーダーが未定義です");
  Material* ret = new Material(*this->shader_resource_);
  this->clones_.emplace_back(ret);
  return ret;
}

T_UINT8 Material::Begin()
{
  INativeShader* shader = this->GetShader();
  shader->SetTechnique(this->technique_);
  return shader->Begin();
}

void Material::BeginPass(T_UINT8 path_id)
{
  INativeShader* shader = this->GetShader();
  shader->BeginPass(path_id);
  if (path_id > 0)
  {
    return;
  }
  for (auto pair : this->properties_)
  {
    pair.second->Apply(shader, pair.first);
  }
}

void Material::SetDefaultProperties(RenderState* state)
{
  INativeShader* shader = this->GetShader();
  shader->SetMatrix("_World", state->GetWorldMatrix());
  //TODO:乗算はGPU側にやらせた方が早いのでは
  shader->SetMatrix("_WorldViewProj", state->GetWorldMatrix() * state->GetViewMatrix() * state->getProjectionMatrix());

  shader->SetVec4f("_CameraPosition", state->GetViewMatrix().GetPosition4d());
  shader->SetVec3f("_CameraDirection", state->GetViewMatrix().GetDirection3d());

  shader->SetTexture("_MainTex", this->texture_);

  shader->SetColor("_Diffuse", this->color_);
}

void Material::CommitChanges()
{
  INativeShader* shader = this->GetShader();
  shader->CommitChanges();
}

void Material::EndPass()
{
  INativeShader* shader = this->GetShader();
  shader->EndPass();
}

void Material::End()
{
  this->GetShader()->End();
}