#pragma once

#include <functional>
#include <vector>
#include <string>
#include "NativeType.h"
#include "NativeAssert.h"
#include "StringUtils.h"
#include "HashUtils.h"

class IAssetLoader
{
  friend class AssetManager;
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~IAssetLoader() {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  virtual void UnloadCache() = 0;

public:
  virtual bool IsMapped() const = 0;
  virtual T_UINT32 GetUniqueID() const = 0;
  virtual T_UINT32 GetSize() const = 0;

};

template<class Resource_>
class AssetLoader : public IAssetLoader
{
  friend class AssetManager;
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  AssetLoader(T_UINT32 uid, const std::string& path)
    : unique_id_(uid)
    , path_("Asset/" + path)
  {
    //本来はアーカイブファイルから取得する
    this->size_ = 1;
  }

  virtual ~AssetLoader()
  {
    this->UnloadCache();
  }

  // =================================================================
  // noncopyable
  // =================================================================
private:
  AssetLoader(const AssetLoader&) = delete;
  AssetLoader& operator = (const AssetLoader&) = delete;
  AssetLoader(AssetLoader&&) = delete;
  AssetLoader& operator = (AssetLoader&&) = delete;

  // =================================================================
  // Methods
  // =================================================================
public:
  operator Resource_*() const
  {
    return this->CreateFromFile();
  }

  Resource_* CreateFromFile() const
  {
    AssetLoader<Resource_>* self = const_cast<AssetLoader<Resource_>*>(this);
    if (!self->cache_)
    {
      //Load時に増えるリファレンスカウントはAssetが管理していることを表すカウント
      self->cache_ = Resource_::CreateFromFile(self->path_.c_str());
    }
    self->cache_->Retain();
    return self->cache_;
  }

  //void CreateFromFileAsync(std::function<void(Resource_*)> func, T_UINT8 priority)
  //{
  //  if (this->cache_)
  //  {
  //    this->cache_->Retain();
  //    func(this->cache_);
  //    return;
  //  }
  //  this->cache_ = this->LoadProcess(this->path_);
  //  func(this->cache_);
  //}

  inline void UnloadCache() override
  {
    this->cache_->Release();
    this->cache_ = nullptr;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline bool IsMapped() const override
  {
    return this->cache_;
  }

  inline T_UINT32 GetUniqueID() const override
  {
    return this->unique_id_;
  }

  inline T_UINT32 GetSize() const override
  {
    return this->size_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  T_UINT32 unique_id_;
  std::string path_;
  T_UINT32 size_;
  Resource_* cache_;
  
};
