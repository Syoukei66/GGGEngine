#include "ResourceManager.h"
#include "Resource.h"

// =================================================================
// Methods
// =================================================================
void ResourceManager::Init()
{
  NATIVE_ASSERT(this->resources_.size() == 0, "準備ができていない状態で追加されたResourceがあります。");
}

void ResourceManager::Uninit()
{
  NATIVE_ASSERT(this->resources_.size() == 0, "Releaseし忘れているResourceがあります。");
}

void ResourceManager::Update()
{
  //TODO:本来ならプラットフォーム側の様子をうかがってアンロードする。
  //使用メモリサイズなどを参考に
  for (auto itr = this->resources_.begin(); itr != this->resources_.end();)
  {
    Resource* resource = (*itr);
    if (resource->GetReferenceCount() == 0)
    {
      delete resource;
      itr = this->resources_.erase(itr);
      continue;
    }
    ++itr;
  }
}

// =================================================================
// Setter / Getter
// =================================================================
size_t ResourceManager::GetMemorySize() const
{
  size_t ret = 0;
  for (Resource* resource : this->resources_)
  {
    ret += resource->GetMemorySize();
  }
  return ret;
}

size_t ResourceManager::GetVideoMemorySize() const
{
  size_t ret = 0;
  for (Resource* resource : this->resources_)
  {
    ret += resource->GetVideoMemorySize();
  }
  return ret;
}
