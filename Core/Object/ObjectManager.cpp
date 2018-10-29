#include "ObjectManager.h"
#include "Object.h"
#include "Ref.h"

// =================================================================
// Methods
// =================================================================
void GGObjectManager::Init()
{
}

void GGObjectManager::Uninit()
{
  // 入れ子になっているオブジェクトもある為。
  // オブジェクトの解放が行われなくなるまでループする。
  while (true)
  {
    bool deleted = false;
    for (auto itr = Instance().objects_.begin(); itr != Instance().objects_.end();)
    {
      const GGObject* obj = (*itr);
      if (obj->GetReferenceCount() == 0)
      {
        delete obj;
        itr = Instance().objects_.erase(itr);
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

  // 未開放のオブジェクトがあれば通知
  for (GGObject* obj : Instance().objects_)
  {
    std::string message = "未開放の";
    message.append(obj->GetObjectName());
    message.append("があります");
    Log::Error(message.c_str());
  }
  GG_ASSERT(Instance().objects_.size() == 0, "未開放のObjectがあります。");
}

void GGObjectManager::Update()
{
  //TODO:本来ならプラットフォーム側の様子をうかがってアンロードする。
  //使用メモリサイズなどを参考に
  for (auto itr = Instance().objects_.begin(); itr != Instance().objects_.end();)
  {
    GGObject* obj = (*itr);
    if (obj->GetReferenceCount() == 0)
    {
      delete obj;
      itr = Instance().objects_.erase(itr);
      continue;
    }
    ++itr;
  }
}

// =================================================================
// Setter / Getter
// =================================================================
size_t GGObjectManager::GetMemorySize()
{
  size_t ret = 0;
  for (GGObject* obj : Instance().objects_)
  {
    ret += obj->GetMemorySize();
  }
  return ret;
}

size_t GGObjectManager::GetVideoMemorySize()
{
  size_t ret = 0;
  for (GGObject* obj : Instance().objects_)
  {
    ret += obj->GetVideoMemorySize();
  }
  return ret;
}
