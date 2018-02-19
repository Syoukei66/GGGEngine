#include "FbxResource.h"
#include "UserResourcePool.h"

// =================================================================
// Factory Method
// =================================================================
FbxResource* FbxResource::DynamicLoad(const char* path)
{
  return UserResourcePool::GetInstance().DynamicLoad<FbxResource>(path);
}

// =================================================================
// Constructor / Destructor
// =================================================================
FbxResource::FbxResource(const char* path)
  : FileResource("FBX File", path)
{}

// =================================================================
// Methods
// =================================================================
FbxData* FbxResource::NativeLoadProcess(const std::string& path)
{
  return FbxData::Create(path.c_str());
}
