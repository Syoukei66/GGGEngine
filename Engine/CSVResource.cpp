#include "CSVResource.h"
#include "UserResourcePool.h"

// =================================================================
// Factory Method
// =================================================================
CSVResource* CSVResource::DynamicLoad(const char* path)
{
  return UserResourcePool::GetInstance().DynamicLoad<CSVResource>(path);
}

// =================================================================
// Constructor / Destructor
// =================================================================
CSVResource::CSVResource(const char* path)
  : FileResource("CSVData", path)
{
}

// =================================================================
// Methods for/from interface/super class
// =================================================================
CSVData* CSVResource::NativeLoadProcess(const std::string& path)
{
  return new CSVData(path.c_str());
}
