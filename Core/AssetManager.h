#pragma once

#include <functional>
#include <unordered_map>
#include <list>

#include "NativeType.h"

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
  inline Asset_* GetAsset(T_UINT32 unique_id)
  {
    return (Asset_*)this->assets_[unique_id];
  }

  template<class Asset_>
  inline Asset_* GetAsset(const std::string& path)
  {
    return (Asset_*)this->assets_[HashUtils::GetHash(path)];
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

  template<class Asset_>
  inline Asset_* AddAsset(const std::string& path)
  {
    return Manage<Asset_>(HashUtils::GetHash(path), StringUtils::GetExtension(path));
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

};