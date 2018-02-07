#include "JsonResource.h"
#include "UserResourcePool.h"

// =================================================================
// Factory Method
// =================================================================
const JsonResource* JsonResource::DynamicLoad(const char* path)
{
  return UserResourcePool::GetInstance().DynamicLoad<JsonResource>(path);
}

// =================================================================
// Constructor / Destructor
// =================================================================
JsonResource::JsonResource(const char* path)
  : FileResource("Json", path)
{}

JsonResource::~JsonResource()
{
}

// =================================================================
// Methods for/from interface/super class
// =================================================================
JsonData* JsonResource::NativeLoadProcess(const std::string& path)
{
  return new JsonData(path.c_str());
}
