#include "ModelResource.h"
#include "UserResourcePool.h"
#include "CerealBinaryModelImporter.h"

ModelResource* ModelResource::DynamicLoad(const char* path)
{
  return UserResourcePool::GetInstance().DynamicLoad<ModelResource>(path);
}

// =================================================================
// Constructor / Destructor
// =================================================================
ModelResource::ModelResource(const char* path)
  : FileResource("Model", path)
{
}

// =================================================================
// Methods
// =================================================================
ModelData* ModelResource::NativeLoadProcess(const std::string& path)
{
  return ModelImporter::Cereal::Binary::Import(path.c_str());
}
