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
  static inline SharedRef<Resource_> Load(T_UINT32 uid)
  {
    NATIVE_ASSERT(uid != 0, "無効なアセットIDが入力されました");
    if (uid > DefaultUniqueID::DEFAULT_UID_BEGIN)
    {
      return ((AssetLoader<Resource_>*)GetInstance()->assets_.at(GetInstance()->unique_id_table_->GetDefaultAssetUniqueID(uid)))->CreateFromFile();
    }
    return ((AssetLoader<Resource_>*)GetInstance()->assets_.at(uid))->CreateFromFile();
  }

  template<class Resource_>
  static inline SharedRef<Resource_> Load(const std::string& path)
  {
    const T_UINT32 uid = GetInstance()->unique_id_table_->GetID(path);
    NATIVE_ASSERT(uid != 0, "無効なアセットIDが入力されました");
    return ((AssetLoader<Resource_>*)GetInstance()->assets_.at(uid))->CreateFromFile();
  }

  template<class Resource_>
  static inline const AssetLoader<Resource_>& GetLoader(T_UINT32 uid)
  {
    NATIVE_ASSERT(uid != 0, "無効なアセットIDが入力されました");
    if (uid > DefaultUniqueID::DEFAULT_UID_BEGIN)
    {
      return (const AssetLoader<Resource_>&)*GetInstance()->assets_.at(GetInstance()->unique_id_table_->GetDefaultAssetUniqueID(uid));
    }
    return (const AssetLoader<Resource_>&)*GetInstance()->assets_.at(uid);
  }

  template<class Resource_>
  static inline const AssetLoader<Resource_>& GetLoader(const std::string& path)
  {
    return (const AssetLoader<Resource_>&)*GetInstance()->assets_.at(GetInstance()->unique_id_table_->GetID(path));
  }

  template<class Resource_>
  static inline const AssetLoader<Resource_>& AddAsset(T_UINT32 uid, const std::string& extension)
  {
    GetInstance()->assets_.emplace(uid, new AssetLoader<Resource_>(uid, std::to_string(uid) + "." + extension));
    return (const AssetLoader<Resource_>&)*GetInstance()->assets_.at(uid);
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
