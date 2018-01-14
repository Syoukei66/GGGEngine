#include "CSVResource.h"
#include "ResourcePool.h"

const CSVResource* CSVResource::DynamicLoad(const char* path)
{
  return ResourcePool::GetInstance().DynamicLoad<CSVResource>(path);
}

CSVResource::CSVResource(const char* path)
  : FileResource("CSVData", path)
{
}

CSVData* CSVResource::NativeLoadProcess(const std::string& path)
{
  return new CSVData(path.c_str());
}
