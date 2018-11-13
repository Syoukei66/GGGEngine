#pragma once

#include "URI.h"

struct Setting;

class AssetConverterManager;
class AssetInfo;
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
  inline void VisitAllEntity(const std::function<void(AssetEntity*)>& func);

  template <class Entity_>
  inline Entity_* ImportImmediately(const URI& uri);

  template <class Entity_>
  inline Entity_* AddEntity(Entity_* entity);

  template <class Entity_>
  inline Entity_* GetEntity(const URI& uri);

  inline T_UINT32 PublishUniqueID(const URI& uri);
  inline T_UINT32 GetUniqueID(const URI& uri) const;
  inline void RegisterDefaultUniqueID(T_UINT32 default_uid, const URI& uri);

  // =================================================================
  // Data Members
  // =================================================================
protected:
  UniqueIdTable* unique_id_table_;
  AssetConverterManager* converter_manager_;

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

inline void AssetConverterContext::VisitAllEntity(const std::function<void(AssetEntity*)>& func)
{
  this->converter_manager_->VisitAllEntity(func);
}

template<class Entity_>
inline Entity_* AssetConverterContext::ImportImmediately(const URI& uri)
{
  return this->converter_manager_->Find<Entity_, Entity_>([&](AssetConverter<Entity_>* converter)
  {
    return converter->ImportImmediately(uri, this);
  });
}

template<class Entity_>
inline Entity_* AssetConverterContext::AddEntity(Entity_* entity)
{
  this->converter_manager_->VisitAll<Entity_>([&](AssetConverter<Entity_>* converter)
  {
    converter->AddEntity(entity);
  });
  return entity;
}

template<class Entity_>
inline Entity_* AssetConverterContext::GetEntity(const URI& uri)
{
  return this->converter_manager_->Find<Entity_, Entity_>([&](AssetConverter<Entity_>* converter)
  {
    return converter->GetEntity(uri);
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
}

