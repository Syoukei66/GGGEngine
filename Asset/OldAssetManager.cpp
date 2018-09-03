#include "OldAssetManager.h"
#include <thread>

// =================================================================
// Constructor / Destructor
// =================================================================
OldAssetManager::OldAssetManager()
  : assets_()
  , loaded_assets_()
  , load_reserve_()
  , unload_reserve_()
  , dynamic_assets_()
{}

OldAssetManager::~OldAssetManager()
{
}

// =================================================================
// Methods
// =================================================================
void OldAssetManager::Uninit()
{
  for (IAssetContainer* asset : this->loaded_assets_)
  {
    asset->Release();
    delete asset;
  }
  this->loaded_assets_.clear();
  this->load_reserve_.clear();
  this->unload_reserve_.clear();

  for (auto& pair : this->engine_assets_)
  {
    delete pair.second;
  }
  this->engine_assets_.clear();

  for (auto& pair : this->dynamic_assets_)
  {
    pair.second->Release();
    delete pair.second;
  }
  this->dynamic_assets_.clear();

  for (auto& pair : this->assets_)
  {
    delete pair.second;
  }
  this->assets_.clear();
}

void OldAssetManager::Update()
{
  std::vector<std::string> delete_assets = std::vector<std::string>();
  for (auto& pair : this->dynamic_assets_)
  {
    if (pair.second->GetReferenceCount() > 0)
    {
      continue;
    }
    delete pair.second;
    delete_assets.emplace_back(pair.first);
  }
  for (std::string& str : delete_assets)
  {
    this->dynamic_assets_.erase(str);
  }
}

void OldAssetManager::ReserveLoad(const IAssetContainer* resource)
{
  this->load_reserve_.insert(const_cast<IAssetContainer*>(resource));
}

//loaded_resources_release �c ���Ƀ��[�h�ς݂�Asset���������ꍇtrue
void OldAssetManager::PreRealize(IAssetLoadingListener* listener, bool loaded_resources_release)
{
  if (listener)
  {
    listener->OnLoadingInit();
  }
  if (loaded_resources_release)
  {
    //���݃��[�h�ς݂�Asset��S�ăA�����[�h�\��
    for (IAssetContainer* asset : this->loaded_assets_)
    {
      this->unload_reserve_.emplace(asset);
    }
  }

  for (auto itr = this->load_reserve_.begin(), end = this->load_reserve_.end(); itr != end;)
  {
    if (this->loaded_assets_.find(*itr) == this->load_reserve_.end())
    {
      ++itr;
      continue;
    }
    //���Ƀ��[�h�ς݂̂��̂Ƀ��[�h�\�񂪗����ꍇ
    //���[�h�A�A�����[�h�\�񂩂�폜
    this->unload_reserve_.erase(*itr);
    itr = this->load_reserve_.erase(itr);
  }

  //���[�h�A�A�����[�h�\������X�i�[�֒ʒm
  if (listener)
  {
    for (IAssetContainer* asset : this->load_reserve_)
    {
      listener->OnLoadingReserved(asset);
    }
    for (IAssetContainer* asset : this->unload_reserve_)
    {
      listener->OnLoadingReserved(asset);
    }
  }
}

void OldAssetManager::Realize(IAssetLoadingListener* listener)
{
  if (listener)
  {
    listener->OnLoadingStarted();
  }

  //�A�����[�h����
  std::thread unload_thread([&]()
  {
    for (IAssetContainer* asset : this->unload_reserve_)
    {
      asset->Release();
      this->loaded_assets_.erase(asset);
      if (listener)
      {
        listener->OnLoadingProgressed(asset);
      }
    }
  });
  //���[�h����
  std::thread load_thread([&]()
  {
    for (IAssetContainer* asset : this->load_reserve_)
    {
      asset->Retain();
      this->loaded_assets_.emplace(asset);
      if (listener)
      {
        listener->OnLoadingProgressed(asset);
      }
    }
  });

  load_thread.join();
  this->load_reserve_.clear();

  unload_thread.join();
  this->unload_reserve_.clear();

  if (listener)
  {
    listener->OnLoadingFinished();
  }
}

