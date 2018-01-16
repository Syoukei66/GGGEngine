#include "Material.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Material::Material()
  : shader_(shader)
  , texture_(nullptr)
  , color_(Color::WHITE)
{
}

Material::~Material()
{
}

// =================================================================
// Method
// =================================================================
