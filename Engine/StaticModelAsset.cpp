#include "StaticModelAsset.h"
#include "UserResourcePool.h"

#include "../Asset/CerealStaticModelIO.h"

StaticModelAsset* StaticModelAsset::DynamicLoad(const char* path)
{
  return UserResourcePool::GetInstance().DynamicLoad<StaticModelAsset>(path);
}

// =================================================================
// Constructor / Destructor
// =================================================================
StaticModelAsset::StaticModelAsset(const char* path)
  : FileResource("StaticModel", path)
{
}

// =================================================================
// Methods
// =================================================================
StaticModelResource* StaticModelAsset::NativeLoadProcess(const std::string& path)
{
  return new StaticModelResource(ModelIO::StaticModel::Import(path.c_str()));
}
