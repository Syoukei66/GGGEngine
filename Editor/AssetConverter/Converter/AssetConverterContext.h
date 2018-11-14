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
  inline bool Reserve(const URI& uri, const URI& source);
  inline void VisitAllEntity(const std::function<void(const SharedRef<AssetEntity>&)>& func);

  template <class Entity_>
  inline SharedRef<Entity_> ImportImmediately(const URI& uri, bool reload);
  inline bool ImportImmediately(const URI& uri, bool reload);

  template <class Entity_>
  inline SharedRef<Entity_> AddEntity(const SharedRef<Entity_>& entity);

  template <class Entity_>
  inline SharedRef<Entity_> GetEntity(const URI& uri);
  inline SharedRef<AssetEntity> GetEntity(T_UINT32 unique_id);

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

inline bool AssetConverterContext::Reserve(const URI& uri, const URI& source)
{
  //Info‚ª¶¬‚³‚ê‚é‚Ü‚ÅConverter‚ð‘–¸
  return this->converter_manager_->Fire([&](IAssetConverter* converter)
  {
    return converter->Reserve(uri, source, this);
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
    Logger::ConvertFaildLog(entity->GetAssetInfo());
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
  return this->converter_manager_->Find<Entity_, Entity_>([&](AssetConverter<Entity_>* converter)
  {
    return converter->GetEntity(uri, this);
  });
}

inline SharedRef<AssetEntity> AssetConverterContext::GetEntity(T_UINT32 unique_id)
{
  return this->converter_manager_->FindAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    return entity->GetAssetInfo()->GetUniqueID() == unique_id;
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

