#pragma once

#include <functional>
#include <vector>
#include <string>
#include "NativeType.h"
#include "NativeAssert.h"
#include "StringUtils.h"
#include "HashUtils.h"

class IAsset
{
  friend class AssetManager;
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~IAsset() {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  virtual void Unload() = 0;
  virtual bool IsNeedUnload() const = 0;

public:
  virtual bool IsMapped() const = 0;

};

template<class Asset_, class Resource_>
class Asset : public IAsset
{
  friend class AssetManager;
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static Asset_* Create(T_UINT32 unique_id, const std::string& extension)
  {
    return AssetManager::GetInstance().AddAsset<Asset_>(unique_id, extension);
  }

  static Asset_* Create(const std::string& path)
  {
    return AssetManager::GetInstance().AddAsset<Asset_>(path);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  Asset(const std::string& path)
    : path_(path)
  {}

  virtual ~Asset()
  {
    NATIVE_ASSERT(!this->resource_, "ResourceをUnloadし忘れています。");
  }

  // =================================================================
  // noncopyable
  // =================================================================
private:
  Asset(const Asset&) = delete;
  Asset& operator = (const Asset&) = delete;
  Asset(Asset&&) = delete;
  Asset& operator = (Asset&&) = delete;

  // =================================================================
  // Methods
  // =================================================================
public:
  void RetainCache() const
  {
    ++const_cast<Asset<Asset_, Resource_>*>(this)->cache_reference_count_;
  }

  void ReleaseCache() const
  {
    NATIVE_ASSERT(this->cache_reference_count_ > 0, "リファレンスカウンタが0の時にReleaseしました");
    --const_cast<Asset<Asset_, Resource_>*>(this)->cache_reference_count_;
  }

  Resource_* CreateFromFile()
  {
    if (this->resource_)
    {
      this->resource_->Retain();
      return this->resource_;
    }
    this->resource_ = this->LoadProcess(this->path_);
    return this->resource_;
  }
  void CreateFromFileAsync(std::function<void(Resource_*)> func, T_UINT8 priority)
  {
    if (this->resource_)
    {
      this->resource_->Retain();
      func(this->resource_);
      return;
    }
    this->resource_ = this->LoadProcess(this->path_);
    func(this->resource_);
  }

protected:
  virtual Resource_* LoadProcess(const std::string& path) = 0;

private:
  inline void Unload() override
  {
    this->resource_->Release();
    this->resource_ = nullptr;
  }

  inline bool IsNeedUnload() const override
  {
    if (!this->resource_)
    {
      return false;
    }
    return this->resource_->GetReferenceCount() <= 1;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline bool IsMapped() const override
  {
    return this->resource_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string path_;
  Resource_* resource_;
  
};
