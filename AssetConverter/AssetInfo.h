#pragma once

#include <string>
#include <functional>

#include "../Core/UniqueIdTable.h"
#include "AssetMetaData.h"

class AssetConverterContext;

class AssetInfo
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static AssetInfo* Create(const std::string& directory_path, const std::string& file_name, const std::string& extension, AssetConverterContext* context);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  AssetInfo() = default;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline T_UINT32 GetUniqueId() const
  {
    return this->meta_data_->GetUniqueId();
  }

  inline const std::string& GetFullPath() const
  {
    return this->full_path_;
  }

  inline const std::string& GetLocalFullPath() const
  {
    return this->local_full_path_;
  }

  inline const std::string& GetDirectoryPath() const
  {
    return this->directory_path_;
  }

  inline const std::string& GetExtension() const
  {
   return this->extension_;
  }

  inline const std::string& GetProgramId() const
  {
    return this->program_id_;
  }

  inline bool UpdateTimeStamp()
  {
    return this->meta_data_->UpdateTimeStamp();
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  AssetMetaData* meta_data_;
  std::string full_path_;
  std::string local_full_path_;
  std::string directory_path_;
  std::string file_name_;
  std::string extension_;
  std::string program_id_;

};
