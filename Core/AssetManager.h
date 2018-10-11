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
  static inline AssetLoader<Resource_>* GetLoader(T_UINT32 uid)
  {
    if (uid == 0)
    {
      return nullptr;
    }
    if (uid > DefaultUniqueID::DEFAULT_UID_BEGIN)
    {
      return (AssetLoader<Resource_>*)GetInstance()->assets_.at(GetInstance()->unique_id_table_->GetDefaultAssetUniqueID(uid));
    }
    return (AssetLoader<Resource_>*)GetInstance()->assets_.at(uid);
  }

  template<class Resource_>
  static inline AssetLoader<Resource_>* GetLoader(const std::string& path)
  {
    return (AssetLoader<Resource_>*)GetInstance()->assets_.at(GetInstance()->unique_id_table_->GetID(path));
  }

  template<class Resource_>
  static inline AssetLoader<Resource_>* AddAsset(T_UINT32 uid, const std::string& extension)
  {
    AssetLoader<Resource_>* ret = new AssetLoader<Resource_>(uid, std::to_string(uid) + "." + extension);
    GetInstance()->assets_.emplace(uid, ret);
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
