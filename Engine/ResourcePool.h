#pragma once

#include <map>
#include <set>
#include "NativeType.h"
#include "ResourceLoader.h"

class IResourceLoadingListener
{
public:
  virtual void OnLoadingInit() {}
  virtual void OnLoadingStarted() {}
  virtual void OnLoadingReserved(const std::string& category, T_UINT8 weight) {}
  virtual void OnLoadingProgressed(const std::string& category, T_UINT8 weight) {}
  virtual void OnLoadingFinished() {}
};

class IResourceLoadReserver
{
public:
  virtual void ReserveLoad(const ResourceLoader& resource) = 0;
};

class ResourcePool : public IResourceLoadReserver
{
public:
  static ResourcePool& GetInstance()
  {
    static ResourcePool self = ResourcePool();
    return self;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  ResourcePool();

public:
  virtual ~ResourcePool();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Init();
  void Uninit();

  //ロード予約を行う
  void ReserveLoad(const ResourceLoader& resource) override;
  //ロード/アンロード予約を作成
  //loaded_resources_release … 既にロード済みのリソースを解放する場合true
  void PreRealize(IResourceLoadingListener* listener, bool loaded_resources_release = true);
  //予約を基にロード/アンロード処理を行う
  void Realize(IResourceLoadingListener* listener);

  template<class T>
  const T* DynamicLoad(const char* path)
  {
    T* ret = (T*)this->resources_[path];
    if (!ret)
    {
      ret = new T(path);
      ret->Load();
      this->resources_[path] = ret;
    }
    return ret;
  }

private:
  std::map<std::string, ResourceLoader*> resources_;

  std::map<std::string, std::set<ResourceLoader*>> load_reserve_;
  std::map<std::string, std::set<ResourceLoader*>> unload_reserve_;
};
