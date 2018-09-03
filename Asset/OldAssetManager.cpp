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

//loaded_resources_release … 既にロード済みのAssetを解放する場合true
void OldAssetManager::PreRealize(IAssetLoadingListener* listener, bool loaded_resources_release)
{
  if (listener)
  {
    listener->OnLoadingInit();
  }
  if (loaded_resources_release)
  {
    //現在ロード済みのAssetを全てアンロード予約
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
    //既にロード済みのものにロード予約が来た場合
    //ロード、アンロード予約から削除
    this->unload_reserve_.erase(*itr);
    itr = this->load_reserve_.erase(itr);
  }

  //ロード、アンロード予約をリスナーへ通知
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

  //アンロード処理
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
  //ロード処理
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

