#include "ResourceManager.h"
#include "Resource.h"

// =================================================================
// Methods
// =================================================================
void ResourceManager::Init()
{
  NATIVE_ASSERT(GetInstance()->resources_.size() == 0, "�������ł��Ă��Ȃ���ԂŒǉ����ꂽResource������܂��B");
}

void ResourceManager::Uninit()
{
  NATIVE_ASSERT(GetInstance()->resources_.size() == 0, "Release���Y��Ă���Resource������܂��B");
}

void ResourceManager::Update()
{
  //TODO:�{���Ȃ�v���b�g�t�H�[�����̗l�q�����������ăA�����[�h����B
  //�g�p�������T�C�Y�Ȃǂ��Q�l��
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
