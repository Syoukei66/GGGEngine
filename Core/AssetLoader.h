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
  virtual void Unload() = 0;
  virtual bool IsNeedUnload() const = 0;

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
    , path_(path)
  {
    //本来はアーカイブファイルから取得する
    this->size_ = 1;
  }

  virtual ~AssetLoader()
  {
    NATIVE_ASSERT(!this->resource_, "ResourceをUnloadし忘れています。");
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
  Resource_* CreateFromFile()
  {
    if (!this->resource_)
    {
      //Load時に増えるリファレンスカウントはAssetが管理していることを表すカウント
      this->resource_ = Resource_::CreateFromFile(this->path_.c_str());
    }
    this->resource_->Retain();
    return this->resource_;
  }

  //void CreateFromFileAsync(std::function<void(Resource_*)> func, T_UINT8 priority)
  //{
  //  if (this->resource_)
  //  {
  //    this->resource_->Retain();
  //    func(this->resource_);
  //    return;
  //  }
  //  this->resource_ = this->LoadProcess(this->path_);
  //  func(this->resource_);
  //}

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
  Resource_* resource_;
  
};
