#include "CustomMaterial.h"
#include "AssetManager.h"
#include "ShaderAsset.h"

// =================================================================
// Factory Method
// =================================================================
rcCustomMaterial* rcCustomMaterial::Create(rcShader* resource, bool protect)
{
  rcCustomMaterial* ret = new rcCustomMaterial(resource, protect);
  ret->Resource::Init();
  return ret;
}

rcCustomMaterial* rcCustomMaterial::Create(const MaterialData& data)
{
  rcShader* resource = AssetManager::GetInstance().GetAsset<ShaderAsset>(data.shader_id_)->CreateFromFile();
  rcCustomMaterial* ret = new rcCustomMaterial(resource, data.protect_);
  for (const auto& pair : data.properties_)
  {
    ret->properties_[pair.first] = pair.second->Clone();
  }
  ret->Resource::Init();
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcCustomMaterial::rcCustomMaterial(rcShader* resource, bool protect)
  : rcMaterial(resource, protect)
  , properties_()
{
}

rcCustomMaterial::~rcCustomMaterial()
{
  for (auto pair : this->properties_)
  {
    delete pair.second;
  }
}

// =================================================================
// Method
// =================================================================
rcMaterial* rcCustomMaterial::CreateClone(rcShader* shader)
{
  return new rcCustomMaterial(shader);
}

void rcCustomMaterial::CopyPropertiesToClone(rcMaterial* clone)
{
  rcCustomMaterial* ret = (rcCustomMaterial*)clone;
  for (auto pair : this->properties_)
  {
    ret->properties_[pair.first] = pair.second->Clone();
  }
}

void rcCustomMaterial::SetProperties(rcShader* shader)
{
  for (auto pair : this->properties_)
  {
    pair.second->Apply(shader, pair.first);
  }
}
