#include "Material.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Material::Material()
{
  this->material_delete_ = true;
  this->material_ = NativeMethod::Material().Material_Create();
}

Material::Material(LP_MATERIAL native_material)
{
  this->material_delete_ = false;
  this->material_ = native_material;
}

Material::~Material()
{
  if (this->material_delete_)
  {
    NativeMethod::Material().Material_Delete(this->material_);
  }
}

// =================================================================
// Method
// =================================================================
void Material::Apply()
{
  NativeMethod::Material().Material_SetAmbient(this->material_, this->ambient_);
  NativeMethod::Material().Material_SetDiffuse(this->material_, this->diffuse_);
}

void Material::SetAmbient(const Color& color)
{
  this->ambient_ = color;
}

void Material::SetAmbient(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
{
  this->ambient_.SetColor(r, g, b, a);
}

void Material::SetDiffuse(const Color& color)
{
  this->diffuse_ = color;
}

void Material::SetDiffuse(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
{
  this->diffuse_.SetColor(r, g, b, a);
}
