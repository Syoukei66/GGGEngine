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

  //���[�h�\����s��
  void ReserveLoad(const ResourceLoader& resource) override;
  //���[�h/�A�����[�h�\����쐬
  //loaded_resources_release �c ���Ƀ��[�h�ς݂̃��\�[�X���������ꍇtrue
  void PreRealize(IResourceLoadingListener* listener, bool loaded_resources_release = true);
  //�\�����Ƀ��[�h/�A�����[�h�������s��
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
