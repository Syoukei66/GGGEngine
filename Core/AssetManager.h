#pragma once

#include <functional>
#include <unordered_map>
#include <list>

#include "AssetLoader.h"
#include "UniqueIdTable.h"

class AssetManager
{
  friend class IAssetLoader;

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  static inline AssetManager* GetInstance()
  {
    static AssetManager self;
    return &self;
  }
  AssetManager() = default;
  ~AssetManager() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  static void Init();
  static void Uninit();
  static void UnloadCaches();

  template<class Resource_>
  static inline AssetLoader<Resource_>* GetLoader(T_UINT32 unique_id)
  {
    return (AssetLoader<Resource_>*)GetInstance()->assets_.at(unique_id);
  }

  template<class Resource_>
  static inline AssetLoader<Resource_>* GetLoader(const std::string& path)
  {
    return (AssetLoader<Resource_>*)GetInstance()->assets_.at(GetInstance()->unique_id_table_->GetID(path));
  }

  template<class Resource_>
  static inline AssetLoader<Resource_>* GetDefaultAssetLoader(T_UINT32 default_uid)
  {
    return (AssetLoader<Resource_>*)GetInstance()->assets_.at(GetInstance()->unique_id_table_->GetDefaultAssetUniqueID(default_uid));
  }

  template<class Resource_>
  static inline AssetLoader<Resource_>* AddAsset(T_UINT32 unique_id, const std::string& extension)
  {
    AssetLoader<Resource_>* ret = new AssetLoader<Resource_>(unique_id, std::to_string(unique_id) + "." + extension);
    GetInstance()->assets_.emplace(unique_id, ret);
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
  std::unordered_map<T_UINT32, IAssetLoader*> assets_;
  UniqueIdTable* unique_id_table_;

};
