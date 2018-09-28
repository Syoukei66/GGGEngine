#pragma once

#include <string>
#include <functional>

#include "UniqueIdTable.h"
#include "AssetMetaData.h"
#include "FileUtil.h"
#include "URI.h"

class AssetConverterContext;

class AssetInfo
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static AssetInfo* Create(const URI& uri, AssetConverterContext* context);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  AssetInfo(const URI& uri);

public:
  ~AssetInfo();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline T_UINT32 GetUniqueID() const
  {
    return this->meta_data_->GetUniqueID();
  }

  inline const URI& GetURI() const
  {
    return this->uri_;
  }

  inline std::string GetInputPath() const
  {
    return FileUtil::CreateInputPath(this->uri_);
  }

  inline std::string GetOutputPath() const
  {
    return FileUtil::CreateOutputPath(std::to_string(this->GetUniqueID()));
  }

  inline bool UpdateTimeStamp()
  {
    return this->meta_data_->UpdateTimeStamp();
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  const URI uri_;
  AssetMetaData* meta_data_;

};
