#pragma once

#include <string>
#include <functional>

#include <Core/UniqueIdTable.h>

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
  GG_INLINE T_UINT32 GetUniqueID() const
  {
    return this->meta_data_->GetUniqueID();
  }

  GG_INLINE const URI& GetURI() const
  {
    return this->uri_;
  }

  GG_INLINE std::string GetInputPath() const
  {
    return FileUtil::CreateInputPath(this->uri_);
  }

  GG_INLINE std::string GetOutputPath() const
  {
    return FileUtil::CreateOutputPath(this);
  }

  GG_INLINE bool UpdateTimeStamp()
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
