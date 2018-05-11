#include "Material.h"
#include "GameObjectRenderState.h"
#include "NativeMethod.h"
#include "Camera.h"
#include "GameObject.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Material::Material(const ShaderResource& resource, bool protect)
  : protected_(protect)
  , shader_resource_(&resource)
  , properties_()
  , color_()
  , texture_()
  , z_test_level_(0)
  , billbording_(false)
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
  ret->z_test_level_ = this->z_test_level_;
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

T_UINT8 Material::Begin()
{
  INativeShader* shader = this->GetShader();
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

void Material::SetDefaultProperties(GameObjectRenderState* state)
{
  INativeShader* shader = this->GetShader();
  shader->SetMatrix("_WorldViewProj", state->GetWorldViewProjToMaterial()->GetNativeInstance());

  shader->SetMatrix("_World", state->GetMatrixStack()->GetTop());
  shader->SetVec4f("_CameraPosition", state->GetCamera()->GetEntity()->GetWorldMatrix().GetPosition4d());
  shader->SetVec3f("_CameraDirection", state->GetCamera()->GetEntity()->GetWorldMatrix().GetDirection3d());

  NativeTextureInstance* texture = this->texture_ ? this->texture_->GetNativeInstance() : nullptr;
  shader->SetTexture("_MainTex", texture);

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