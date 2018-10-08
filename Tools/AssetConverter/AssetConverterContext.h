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
  inline bool Reserve(const URI& uri);

  template <class Entity_>
  inline Entity_* ImportImmediately(const URI& uri);

  template <class Entity_>
  inline Entity_* AddEntity(Entity_* entity);

  template <class Entity_>
  inline Entity_* GetEntity(const URI& uri);

  inline T_UINT32 PublishUniqueID(const URI& uri);
  inline T_UINT32 GetUniqueID(const URI& uri) const;

  // =================================================================
  // Data Members
  // =================================================================
protected:
  UniqueIdTable* unique_id_table_;
  AssetConverterManager* converter_manager_;

};

#include "AssetConverterManager.h"

inline bool AssetConverterContext::Reserve(const URI& uri)
{
  //Info�����������܂�Converter�𑖍�
  return this->converter_manager_->Fire([&](IAssetConverter* converter)
  {
    return converter->Reserve(uri, this);
  });
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

