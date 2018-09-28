#pragma once

#include <string>
#include "UniqueIdTable.h"
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
  AssetConverterContext(const Setting* setting, AssetConverterManager* converter_manager);
  virtual ~AssetConverterContext();

  // =================================================================
  // Methods
  // =================================================================
public:
  AssetInfo* Reserve(const URI& uri);

  template <class Entity_>
  Entity_* ImportImmediately(const URI& uri);

  template <class Entity_>
  Entity_* AddEntity(Entity_* entity);

  template <class Entity_>
  Entity_* GetEntity(const URI& uri);

  inline T_UINT32 PublishUniqueID(const URI& uri);
  inline T_UINT32 GetUniqueID(const URI& uri) const;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const Setting* GetSetting() const
  {
    return this->setting_;
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  const Setting* setting_;
  UniqueIdTable* unique_id_table_;
  AssetConverterManager* converter_manager_;
  std::unordered_map<T_UINT32, AssetInfo*> infos_;

};

#include "AssetConverterManager.h"

template<class Entity_>
inline Entity_* AssetConverterContext::ImportImmediately(const URI& uri)
{
  //既にインポート済みであればそのAssetEntityをリターン
  const auto& itr = this->infos_.find(this->PublishUniqueID(uri));
  if (itr != this->infos_.end())
  {
    AssetInfo* info = itr->second;
    return this->converter_manager_->Find<Entity_, Entity_>([&](AssetConverter<Entity_>* converter)
    {
      return converter->GetEntity(info);
    });
  }
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
  return this->unique_id_table_->Publish(uri.GetFullPath());
}

inline T_UINT32 AssetConverterContext::GetUniqueID(const URI& uri) const
{
  return this->unique_id_table_->GetID(uri.GetFullPath());
}

