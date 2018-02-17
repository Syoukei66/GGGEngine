#include "JsonResource.h"
#include "UserResourcePool.h"

// =================================================================
// Factory Method
// =================================================================
JsonResource* JsonResource::DynamicLoad(const char* path)
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
{}

// =================================================================
// Methods for/from interface/super class
// =================================================================
JsonData* JsonResource::NativeLoadProcess(const std::string& path)
{
  JsonData* ret = new JsonData();
  ret->Read(path.c_str());
  return ret;
}
