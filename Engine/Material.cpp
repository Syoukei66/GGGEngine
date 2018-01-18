#include "Material.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Material::Material(const ShaderResource& resource)
  : Material(resource.GetContents())
{
}

Material::Material(INativeShader* shader)
  : shader_(shader)
  , properties_()
  , color_()
  , texture_()
{
  this->color_ = &(Color4F(this->ColorProperty("_Diffuse")));
  this->texture_ = &((const Texture*)(this->TextureProperty("_MainTex")));
}

Material::~Material()
{
}

// =================================================================
// Method
// =================================================================
void Material::Begin()
{
  this->shader_->Begin();
  //for (auto pair : this->properties_)
  //{
  //  pair.second->Apply(this->shader_, pair.first);
  //}
  this->properties_["_WorldViewProj"]->Apply(this->shader_, "_WorldViewProj");
  this->shader_->CommitChanges();
}

void Material::End()
{
  this->shader_->End();
}