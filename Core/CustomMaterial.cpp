#include "CustomMaterial.h"

// =================================================================
// Constructor / Destructor
// =================================================================
CustomMaterial::CustomMaterial(rcShader* resource, bool protect)
  : Material(resource, protect)
  , properties_()
{
}

CustomMaterial::~CustomMaterial()
{
  for (auto pair : this->properties_)
  {
    delete pair.second;
  }
}

// =================================================================
// Method
// =================================================================
Material* CustomMaterial::CreateClone(rcShader* shader)
{
  return new CustomMaterial(shader);
}

void CustomMaterial::CopyPropertiesToClone(Material* clone)
{
  CustomMaterial* ret = (CustomMaterial*)clone;
  for (auto pair : this->properties_)
  {
    ret->properties_[pair.first] = pair.second->Clone();
  }
}

void CustomMaterial::SetProperties(rcShader* shader)
{
  for (auto pair : this->properties_)
  {
    pair.second->Apply(shader, pair.first);
  }
}
