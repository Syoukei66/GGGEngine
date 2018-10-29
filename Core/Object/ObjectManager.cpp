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
  // ����q�ɂȂ��Ă���I�u�W�F�N�g������ׁB
  // �I�u�W�F�N�g�̉�����s���Ȃ��Ȃ�܂Ń��[�v����B
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

  // ���J���̃I�u�W�F�N�g������Βʒm
  for (GGObject* obj : Instance().objects_)
  {
    std::string message = "���J����";
    message.append(obj->GetObjectName());
    message.append("������܂�");
    Log::Error(message.c_str());
  }
  GG_ASSERT(Instance().objects_.size() == 0, "���J����Object������܂��B");
}

void GGObjectManager::Update()
{
  //TODO:�{���Ȃ�v���b�g�t�H�[�����̗l�q�����������ăA�����[�h����B
  //�g�p�������T�C�Y�Ȃǂ��Q�l��
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
