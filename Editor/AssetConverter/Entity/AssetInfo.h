#pragma once

#include "AssetMetaData.h"
#include <Util/FileUtil.h>
#include "URI.h"

class AssetConverterContext;

class AssetInfo
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static AssetInfo* Create(const URI& uri, AssetConverterContext* context);
  static AssetInfo* Create(const URI& uri, T_UINT32 source_unique_id, AssetConverterContext* context);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  AssetInfo(AssetMetaData* meta_data);

public:
  ~AssetInfo();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const AssetMetaData* GetMetaData() const
  {
    return this->meta_data_;
  }

  inline AssetMetaData* GetMetaData()
  {
    return this->meta_data_;
  }

  inline T_UINT32 GetUniqueID() const
  {
    return this->meta_data_->GetUniqueID();
  }

  inline T_UINT32 GetSourceUniqueId() const
  {
    return this->meta_data_->GetSourceUniqueId();
  }

  inline const URI& GetURI() const
  {
    return this->meta_data_->GetURI();
  }

  inline std::string GetInputPath() const
  {
    return FileUtil::CreateInputPath(this->GetURI());
  }

  inline std::string GetOutputPath() const
  {
    return FileUtil::CreateArchivePath(this);
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

};
