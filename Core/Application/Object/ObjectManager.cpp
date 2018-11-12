#include "ObjectManager.h"
#include "Object.h"
#include "Ref.h"

// =================================================================
// Methods
// =================================================================
void GGObjectManager::GC()
{
  // ����q�ɂȂ��Ă���I�u�W�F�N�g������ׁB
  // �I�u�W�F�N�g�̉�����s���Ȃ��Ȃ�܂Ń��[�v����B
  while (true)
  {
    bool deleted = false;
    for (auto itr = Self().objects_.begin(); itr != Self().objects_.end();)
    {
      const GGObject* obj = (*itr);
      if (obj->GetReferenceCount() == 0)
      {
        delete obj;
        itr = Self().objects_.erase(itr);
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
}

bool GGObjectManager::CheckLeak()
{
  GGObjectManager* self = &Self();
  // ���J���̃I�u�W�F�N�g������Βʒm
  for (GGObject* obj : self->objects_)
  {
    std::string message = "���J����";
    message.append(obj->GetObjectName());
    message.append("������܂�");
    Log::Error(message.c_str());
  }
  return self->objects_.size() > 0;
}

void GGObjectManager::Update()
{
  //TODO:�{���Ȃ�v���b�g�t�H�[�����̗l�q�����������ăA�����[�h����B
  //�g�p�������T�C�Y�Ȃǂ��Q�l��
  for (auto itr = Self().objects_.begin(); itr != Self().objects_.end();)
  {
    GGObject* obj = (*itr);
    if (obj->GetReferenceCount() == 0)
    {
      delete obj;
      itr = Self().objects_.erase(itr);
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
  for (GGObject* obj : Self().objects_)
  {
    ret += obj->GetMemorySize();
  }
  return ret;
}

size_t GGObjectManager::GetVideoMemorySize()
{
  size_t ret = 0;
  for (GGObject* obj : Self().objects_)
  {
    ret += obj->GetVideoMemorySize();
  }
  return ret;
}
