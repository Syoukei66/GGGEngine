#include "ResourcePool.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ResourcePool::ResourcePool()
  : resources_()
  , load_reserve_()
  , unload_reserve_()
{}

ResourcePool::~ResourcePool()
{

}

// =================================================================
// Methods
// =================================================================
void ResourcePool::Init()
{
  this->Uninit();
}

void ResourcePool::Uninit()
{
  for (auto itr = this->resources_.begin(), end = this->resources_.end(); itr != end; ++itr)
  {
    itr->second->Unload();
  }
  this->resources_.clear();
  this->load_reserve_.clear();
  this->unload_reserve_.clear();
}

void ResourcePool::ReserveLoad(const ResourceLoader& resource)
{
  this->load_reserve_[resource.GetCategory()].insert(const_cast<ResourceLoader*>(&resource));
}

//loaded_resources_release �c ���Ƀ��[�h�ς݂̃��\�[�X���������ꍇtrue
void ResourcePool::PreRealize(IResourceLoadingListener* listener, bool loaded_resources_release)
{
  listener->OnLoadingInit();
  if (loaded_resources_release)
  {
    //���݃��[�h�ς݂̃��\�[�X��S�ăA�����[�h�\��
    for (auto itr = this->resources_.begin(), end = this->resources_.end(); itr != end; ++itr)
    {
      this->unload_reserve_[itr->second->GetCategory()].insert(itr->second);
    }
  }

  for (auto itr = this->load_reserve_.begin(), end = this->load_reserve_.end(); itr != end; ++itr)
  {
    for (auto itr2 = itr->second.begin(); itr2 != itr->second.end();)
    {
      //���Ƀ��[�h�ς݂̂��̂Ƀ��[�h�\�񂪗����ꍇ
      if (this->resources_.find((*itr2)->GetPath()) != this->resources_.end())
      {
        //���[�h�A�A�����[�h�\�񂩂�폜
        this->unload_reserve_[itr->first].erase(*itr2);
        itr2 = itr->second.erase(itr2);
        continue;
      }
      ++itr2;
    }
  }

  //���[�h�A�A�����[�h�\������X�i�[�֒ʒm
  for (auto itr = this->unload_reserve_.begin(), end = this->unload_reserve_.end(); itr != end; ++itr)
  {
    listener->OnLoadingReserved(itr->first, itr->second.size());
  }
  for (auto itr = this->load_reserve_.begin(), end = this->load_reserve_.end(); itr != end; ++itr)
  {
    listener->OnLoadingReserved(itr->first, itr->second.size());
  }
}

void ResourcePool::Realize(IResourceLoadingListener* listener)
{
  listener->OnLoadingStarted();

  //�A�����[�h����
  for (auto itr = this->unload_reserve_.begin(), end = this->unload_reserve_.end(); itr != end; ++itr)
  {
    for (auto itr2 = itr->second.begin(), end2 = itr->second.end(); itr2 != end2; ++itr2)
    {
      (*itr2)->Unload();
      this->resources_.erase((*itr2)->GetPath());
      listener->OnLoadingProgressed(itr->first, 1);
    }
  }

  //���[�h����
  for (auto itr = this->load_reserve_.begin(), end = this->load_reserve_.end(); itr != end; ++itr)
  {
    for (auto itr2 = itr->second.begin(), end2 = itr->second.end(); itr2 != end2; ++itr2)
    {
      (*itr2)->Load();
      this->resources_[(*itr2)->GetPath()] = (*itr2);
      listener->OnLoadingProgressed(itr->first, 1);
    }
  }

  this->load_reserve_.clear();
  this->unload_reserve_.clear();

  listener->OnLoadingFinished();
}

