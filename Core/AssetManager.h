#pragma once

#include <functional>
#include <unordered_map>
#include <list>

#include "NativeType.h"
#include "DefaultUniqueID.h"

class IAsset;

class AssetManager
{
  friend class IAsset;
public:
  static inline AssetManager& GetInstance()
  {
    static AssetManager self;
    return self;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetManager() = default;
  ~AssetManager() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  void Init();
  void Uninit();
  void Update();

  template<class Asset_>
  inline Asset_* GetAsset(T_UINT32 unique_id) const
  {
    return (Asset_*)this->assets_.at(unique_id);
  }

  template<class Asset_>
  inline Asset_* GetDefaultAsset(T_UINT32 default_uid) const
  {
    return (Asset_*)this->assets_.at(this->default_uids_->GetUniqueId(default_uid));
  }

private:
  template<class Asset_>
  inline Asset_* AddAsset(T_UINT32 unique_id, const std::string& extension)
  {
    Asset_* ret = new Asset_(std::to_string(unique_id) + "." + extension);
    AssetManager::GetInstance().Manage(unique_id, ret);
    this->assets_.emplace(unique_id, asset);
    return ret;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  //size_t GetMemorySize() const;
  //size_t GetVideoMemorySize() const;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<T_UINT32, IAsset*> assets_;
  DefaultUniqueID* default_uids_;

};
