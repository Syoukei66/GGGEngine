#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "NativeType.h"
#include "NativeAssert.h"
#include "ResourceLoader.h"
#include "FileLoader.h"

#ifdef _DEBUG
#include <fstream>
#endif

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
  virtual void ReserveLoad(const FileLoader& resource) = 0;
};

class ResourcePool : public IResourceLoadReserver
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ResourcePool();
  virtual ~ResourcePool();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Init();
  void Uninit();

  void Update();

  //ロード予約を行う
  void ReserveLoad(const FileLoader& resource) override;
  //ロード/アンロード予約を作成
  //loaded_resources_release … 既にロード済みのリソースを解放する場合true
  void PreRealize(IResourceLoadingListener* listener, bool loaded_resources_release = true);
  //予約を基にロード/アンロード処理を行う
  void Realize(IResourceLoadingListener* listener);

  template<class T>
  T* DynamicLoad(const char* path)
  {
    T* ret = (T*)this->dynamic_resources_[path];
    if (!ret)
    {
#ifdef _DEBUG
      std::ifstream ifs(path);
      NATIVE_ASSERT(ifs.is_open(), "ファイルパスが間違えています");
#endif
      ret = new T(path);
      ret->Load();
      this->dynamic_resources_[path] = ret;
    }
    ret->Retain();
    return ret;
  }

private:
  std::unordered_map<std::string, FileLoader*> resources_;
  std::unordered_map<std::string, std::unordered_set<FileLoader*>> load_reserve_;
  std::unordered_map<std::string, std::unordered_set<FileLoader*>> unload_reserve_;

  //動的リソースは動的生成される為、deleteする必要がある
  std::unordered_map<std::string, FileLoader*> dynamic_resources_;
};
