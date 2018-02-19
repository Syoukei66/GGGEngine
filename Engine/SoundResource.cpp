#include "SoundResource.h"
#include "UserResourcePool.h"

SoundResource* SoundResource::DynamicLoad(const char* path)
{
  return UserResourcePool::GetInstance().DynamicLoad<SoundResource>(path);
}

SoundResource::SoundResource(const char* path)
  : FileResource("Sound", path)
{
}

INativeSound* SoundResource::NativeLoadProcess(const std::string& path)
{
  return INativeSound::Create(path.c_str());
}
