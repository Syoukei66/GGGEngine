#include "Material.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Material::Material()
  : texture_(nullptr)
  , color_(Color::WHITE)
  , blend_function_src_(BlendFunction::BLEND_DEFAULT_SRC)
  , blend_function_dst_(BlendFunction::BLEND_DEFAULT_DST)
{
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
}

void Material::End()
{
  this->shader_->End();
}