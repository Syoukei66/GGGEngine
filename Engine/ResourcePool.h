#pragma once

#include <map>
#include <set>
#include <string>

class IResourceLoadingProgressListener
{
public:
  virtual void OnLoadingReserved(const std::string& category, T_UINT8 weight) {};
  virtual void OnLoadingProgressed(const std::string& category, T_UINT8 weight) {};
};

class IResourceLoadingListener : public IResourceLoadingProgressListener
{
public:
  virtual void OnLoadingInit() {};
  virtual void OnLoadingStarted() {};
  virtual void OnLoadingFinished() {};
};

template<typename TKey>
class ResourceLoadReserver
{
public:
  virtual void ReserveLoad(const TKey& key) = 0;
};

template<typename TKey, typename TValue>
class ResourcePool : public ResourceLoadReserver<TKey>
{
public:
  ResourcePool(const std::string& category)
    : category_(category)
  {
  }

  virtual ~ResourcePool()
  {
    for (typename std::map<TKey, TValue*>::iterator itr = this->resources_.begin(); itr != this->resources_.end();)
    {
      //this->UnloadProcess(itr->first, itr->second);
      itr = this->resources_.erase(itr);
    }
  }

  //ロード予約とアンロード予約を行い
  //Realize処理で実ロード/アンロード処理を行う
public:
  void ReserveLoad(const TKey& key) override
  {
    this->load_reserve_.insert(key);
  }

  //loaded_resources_release … 既にロード済みのリソースを解放する場合true
  void PreRealize(IResourceLoadingProgressListener* listener, bool loaded_resources_release = true)
  {
    if (loaded_resources_release)
    {
      //現在ロード済みのリソースを全てアンロード予約
      for (std::map<TKey, TValue*>::iterator itr = this->resources_.begin(); itr != this->resources_.end(); ++itr)
      {
        this->unload_reserve_[itr->first] = itr->second;
      }
    }

    for (std::set<TKey>::iterator itr = this->load_reserve_.begin(); itr != this->load_reserve_.end();)
    {
      //既にロード済みのものにロード予約が来た場合
      if (this->resources_.find(*itr) != this->resources_.end())
      {
        //ロード、アンロード予約から削除
        this->unload_reserve_.erase(*itr);
        itr = this->load_reserve_.erase(itr);
        continue;
      }
      ++itr;
    }

    //ロード、アンロード予約をリスナーへ通知
    for (std::map<TKey, TValue*>::iterator itr = this->unload_reserve_.begin(); itr != this->unload_reserve_.end(); ++itr)
    {
      this->PreUnloadProcess(itr->first, itr->second);
      listener->OnLoadingReserved(this->category_, 1);
    }
    for (std::set<TKey>::iterator itr = this->load_reserve_.begin(); itr != this->load_reserve_.end(); ++itr)
    {
      this->resources_[*itr] = this->PreLoadProcess(*itr);
      listener->OnLoadingReserved(this->category_, 1);
    }
  }

  void Realize(IResourceLoadingProgressListener* listener)
  {
    //アンロード処理
    for (std::map<TKey, TValue*>::iterator itr = this->unload_reserve_.begin(); itr != this->unload_reserve_.end(); ++itr)
    {
      this->UnloadProcess(itr->first, itr->second);
      this->resources_.erase(itr->first);
      listener->OnLoadingProgressed(this->category_, 1);
    }

    //ロード処理
    for (std::set<TKey>::iterator itr = this->load_reserve_.begin(); itr != this->load_reserve_.end(); ++itr)
    {
      this->resources_[*itr] = this->LoadProcess(*itr, this->resources_[*itr]);
      listener->OnLoadingProgressed(this->category_, 1);
    }

    this->load_reserve_.clear();
    this->unload_reserve_.clear();
  }

protected:
  virtual TValue* PreLoadProcess(const TKey& key) = 0;
  virtual TValue* LoadProcess(const TKey& key, TValue* value) = 0;
  virtual void PreUnloadProcess(const TKey& key, TValue* value) = 0;
  virtual void UnloadProcess(const TKey& key, TValue* value) = 0;

public:
  T_UINT32 Size()
  {
    return this->resources_.size();
  }
  TValue* Get(const TKey& key)
  {
    return this->resources_[key];
  }

private:
  std::string category_;
  std::map<TKey, TValue*> resources_;
  std::set<TKey> load_reserve_;
  std::map<TKey, TValue*> unload_reserve_;
};
