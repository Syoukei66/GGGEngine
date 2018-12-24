#pragma once

#include "URI.h"

struct Setting;

class AssetConverterManager;
class AssetMetaData;
class UniqueIdTable;
class AssetEntity;

class AssetConverterContext
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverterContext(UniqueIdTable* unique_id_table, AssetConverterManager* converter_manager);
  virtual ~AssetConverterContext() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  inline bool Reserve(const URI& uri);
  inline bool Reserve(const URI& uri, T_UINT32 source_unique_id);
  inline void VisitAllEntity(const std::function<void(const SharedRef<AssetEntity>&)>& func);

  template <class Entity_>
  inline SharedRef<Entity_> ImportImmediately(const URI& uri, bool reload);
  inline bool ImportImmediately(const URI& uri, bool reload);

  template <class Entity_>
  inline SharedRef<Entity_> AddEntity(const SharedRef<Entity_>& entity);

  template <class Entity_>
  inline SharedRef<Entity_> GetEntity(const URI& uri);
  inline SharedRef<AssetEntity> GetEntity(const URI& uri);
  template <class Entity_>
  inline SharedRef<Entity_> GetEntity(T_UINT32 unique_id);
  inline SharedRef<AssetEntity> GetEntity(T_UINT32 unique_id);

  inline T_UINT32 PublishUniqueID(const URI& uri);
  inline T_UINT32 GetUniqueID(const URI& uri) const;
  inline void RegisterDefaultUniqueID(T_UINT32 default_uid, const URI& uri);

  inline const URI& GetDefaultAssetURI(T_UINT32 default_uid);

  // =================================================================
  // Data Members
  // =================================================================
protected:
  UniqueIdTable* unique_id_table_;
  AssetConverterManager* converter_manager_;
  std::unordered_map<T_UINT32, URI> default_asset_uri_;

};

#include "AssetConverterManager.h"
#include <Core/Application/Asset/UniqueIdTable.h>

inline AssetConverterContext::AssetConverterContext(UniqueIdTable* unique_id_table, AssetConverterManager* converter_manager)
  : unique_id_table_(unique_id_table)
  , converter_manager_(converter_manager)
{
}

inline bool AssetConverterContext::Reserve(const URI& uri)
{
  //Info‚ª¶¬‚³‚ê‚é‚Ü‚ÅConverter‚ð‘–¸
  return this->converter_manager_->Fire([&](IAssetConverter* converter)
  {
    return converter->Reserve(uri, this);
  });
}

inline bool AssetConverterContext::Reserve(const URI& uri, T_UINT32 source_unique_id)
{
  //Info‚ª¶¬‚³‚ê‚é‚Ü‚ÅConverter‚ð‘–¸
  return this->converter_manager_->Fire([&](IAssetConverter* converter)
  {
    return converter->Reserve(uri, source_unique_id, this);
  });
}

inline void AssetConverterContext::VisitAllEntity(const std::function<void(const SharedRef<AssetEntity>&)>& func)
{
  this->converter_manager_->VisitAllEntity(func);
}

template<class Entity_>
inline SharedRef<Entity_> AssetConverterContext::ImportImmediately(const URI& uri, bool reload)
{
  return this->converter_manager_->Find<Entity_>([&](AssetConverter<Entity_>* converter)
  {
    if (converter->ImportImmediately(uri, this, reload))
    {
      return converter->GetEntity(uri, this);
    }
    return SharedRef<Entity_>(nullptr);
  });
}

inline bool AssetConverterContext::ImportImmediately(const URI& uri, bool reload)
{
  return this->converter_manager_->Fire([&](IAssetConverter* converter)
  {
    return converter->ImportImmediately(uri, this, reload);
  });
}

template<class Entity_>
inline SharedRef<Entity_> AssetConverterContext::AddEntity(const SharedRef<Entity_>& entity)
{
  if (!entity)
  {
    Logger::ConvertFaildLog(entity->GetMetaData());
    return nullptr;
  }
  this->converter_manager_->VisitAll<Entity_>([&](AssetConverter<Entity_>* converter)
  {
    converter->AddEntity(entity);
  });
  return entity;
}

template<class Entity_>
inline SharedRef<Entity_> AssetConverterContext::GetEntity(const URI& uri)
{
  return this->converter_manager_->Find<Entity_>([&](AssetConverter<Entity_>* converter)
  {
    return converter->GetEntity(uri, this);
  });
}

inline SharedRef<AssetEntity> AssetConverterContext::GetEntity(const URI& uri)
{
  return this->converter_manager_->FindAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    return entity->GetMetaData()->GetURI() == uri;
  });
}

template<class Entity_>
inline SharedRef<Entity_> AssetConverterContext::GetEntity(T_UINT32 unique_id)
{
  if (unique_id > DefaultUniqueID::DEFAULT_UID_BEGIN)
  {
    unique_id = this->unique_id_table_->GetDefaultAssetUniqueID(unique_id);
  }
  return this->converter_manager_->Find<Entity_>([&](AssetConverter<Entity_>* converter)
  {
    return converter->GetEntity(unique_id);
  });
}

inline SharedRef<AssetEntity> AssetConverterContext::GetEntity(T_UINT32 unique_id)
{
  if (unique_id > DefaultUniqueID::DEFAULT_UID_BEGIN)
  {
    unique_id = this->unique_id_table_->GetDefaultAssetUniqueID(unique_id);
  }
  return this->converter_manager_->FindAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    return entity->GetMetaData()->GetUniqueID() == unique_id;
  });
}

inline T_UINT32 AssetConverterContext::PublishUniqueID(const URI& uri)
{
  return this->unique_id_table_->Publish(FileUtil::CreateRuntimeAssetPath(uri));
}

inline T_UINT32 AssetConverterContext::GetUniqueID(const URI& uri) const
{
  return this->unique_id_table_->GetID(FileUtil::CreateRuntimeAssetPath(uri));
}

inline void AssetConverterContext::RegisterDefaultUniqueID(T_UINT32 default_uid, const URI& uri)
{
  this->unique_id_table_->RegisterDefaultAssetUniqueID(default_uid, FileUtil::CreateRuntimeAssetPath(uri));
  this->default_asset_uri_[default_uid] = uri;
}

inline const URI& AssetConverterContext::GetDefaultAssetURI(T_UINT32 default_uid)
{
  return this->default_asset_uri_[default_uid];
}

