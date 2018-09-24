#pragma once

#include <string>
#include "../Core/UniqueIdTable.h"
#include "Setting.h"

class AssetConverterManager;

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
  AssetInfo* Reserve(const std::string& directory_path, const std::string& file_name, const std::string& extension);

  template <class Entity_>
  Entity_* ImportImmediately(const std::string& directory_path, const std::string& file_name, const std::string& extension);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const Setting* GetSetting() const
  {
    return this->setting_;
  }

  inline UniqueIdTable* GetUniqueIdTable() const
  {
    return this->unique_id_table_;
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  const Setting* setting_;
  UniqueIdTable* unique_id_table_;
  AssetConverterManager* converter_manager_;

};

#include "AssetConverterManager.h"

template<class Entity_>
inline Entity_* AssetConverterContext::ImportImmediately(const std::string& directory_path, const std::string& file_name, const std::string& extension)
{
  return this->converter_manager_->Find<Entity_, Entity_>([&](AssetConverter<Entity_>* converter)
  {
    return converter->ImportImmediately(directory_path, file_name, extension, this);
  });
}
