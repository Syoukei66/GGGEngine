#include "ResourceManager.h"
#include "Resource.h"

// =================================================================
// Methods
// =================================================================
void ResourceManager::Init()
{
  NATIVE_ASSERT(GetInstance()->resources_.size() == 0, "準備ができていない状態で追加されたResourceがあります。");
}

void ResourceManager::Uninit()
{
  // デストラクタでRelease処理を行うリソースもある為
  while (true)
  {
    bool deleted = false;
    for (auto itr = GetInstance()->resources_.begin(); itr != GetInstance()->resources_.end();)
    {
      Resource* resource = (*itr);
      if (resource->GetReferenceCount() == 0)
      {
        delete resource;
        itr = GetInstance()->resources_.erase(itr);
        deleted = true;
        continue;
      }
      ++itr;
    }
    if (!deleted)
    {
      break;
    }
  }
  for (Resource* resource : GetInstance()->resources_)
  {
    std::string message = "未開放の";
    message.append(resource->GetResourceName());
    message.append("があります");
    Log::Error(message.c_str());
  }
  NATIVE_ASSERT(GetInstance()->resources_.size() == 0, "Releaseし忘れているResourceがあります。");
}

void ResourceManager::Update()
{
  //TODO:本来ならプラットフォーム側の様子をうかがってアンロードする。
  //使用メモリサイズなどを参考に
  for (auto itr = GetInstance()->resources_.begin(); itr != GetInstance()->resources_.end();)
  {
    Resource* resource = (*itr);
    if (resource->GetReferenceCount() == 0)
    {
      delete resource;
      itr = GetInstance()->resources_.erase(itr);
      continue;
    }
    ++itr;
  }
}

// =================================================================
// Setter / Getter
// =================================================================
size_t ResourceManager::GetMemorySize()
{
  size_t ret = 0;
  for (Resource* resource : GetInstance()->resources_)
  {
    ret += resource->GetMemorySize();
  }
  return ret;
}

size_t ResourceManager::GetVideoMemorySize()
{
  size_t ret = 0;
  for (Resource* resource : GetInstance()->resources_)
  {
    ret += resource->GetVideoMemorySize();
  }
  return ret;
}
