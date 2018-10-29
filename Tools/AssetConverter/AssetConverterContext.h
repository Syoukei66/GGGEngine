#pragma once

#include <string>
#include <Core/UniqueIdTable.h>
#include "URI.h"

struct Setting;

class AssetConverterManager;
class AssetInfo;

class AssetConverterContext
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverterContext(UniqueIdTable* unique_id_table, AssetConverterManager* converter_manager)
    : unique_id_table_(unique_id_table)
    , converter_manager_(converter_manager)
  {
  }
  virtual ~AssetConverterContext() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  GG_INLINE bool Reserve(const URI& uri);

  template <class Entity_>
  GG_INLINE Entity_* ImportImmediately(const URI& uri);

  template <class Entity_>
  GG_INLINE Entity_* AddEntity(Entity_* entity);

  template <class Entity_>
  GG_INLINE Entity_* GetEntity(const URI& uri);

  GG_INLINE T_UINT32 PublishUniqueID(const URI& uri);
  GG_INLINE T_UINT32 GetUniqueID(const URI& uri) const;
  GG_INLINE void RegisterDefaultUniqueID(T_UINT32 default_uid, const URI& uri);

  // =================================================================
  // Data Members
  // =================================================================
protected:
  UniqueIdTable* unique_id_table_;
  AssetConverterManager* converter_manager_;

};

#include "AssetConverterManager.h"

GG_INLINE bool AssetConverterContext::Reserve(const URI& uri)
{
  //Info‚ª¶¬‚³‚ê‚é‚Ü‚ÅConverter‚ð‘–¸
  return this->converter_manager_->Fire([&](IAssetConverter* converter)
  {
    return converter->Reserve(uri, this);
  });
}

template<class Entity_>
GG_INLINE Entity_* AssetConverterContext::ImportImmediately(const URI& uri)
{
  return this->converter_manager_->Find<Entity_, Entity_>([&](AssetConverter<Entity_>* converter)
  {
    return converter->ImportImmediately(uri, this);
  });
}

template<class Entity_>
GG_INLINE Entity_* AssetConverterContext::AddEntity(Entity_* entity)
{
  this->converter_manager_->VisitAll<Entity_>([&](AssetConverter<Entity_>* converter)
  {
    converter->AddEntity(entity);
  });
  return entity;
}

template<class Entity_>
GG_INLINE Entity_* AssetConverterContext::GetEntity(const URI& uri)
{
  return this->converter_manager_->Find<Entity_, Entity_>([&](AssetConverter<Entity_>* converter)
  {
    return converter->GetEntity(uri);
  });
}

GG_INLINE T_UINT32 AssetConverterContext::PublishUniqueID(const URI& uri)
{
  return this->unique_id_table_->Publish(FileUtil::CreateRuntimeAssetPath(uri));
}

GG_INLINE T_UINT32 AssetConverterContext::GetUniqueID(const URI& uri) const
{
  return this->unique_id_table_->GetID(FileUtil::CreateRuntimeAssetPath(uri));
}

GG_INLINE void AssetConverterContext::RegisterDefaultUniqueID(T_UINT32 default_uid, const URI& uri)
{
  this->unique_id_table_->RegisterDefaultAssetUniqueID(default_uid, FileUtil::CreateRuntimeAssetPath(uri));
}

