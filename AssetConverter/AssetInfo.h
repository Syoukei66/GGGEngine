#pragma once

#include <string>
#include <functional>

#include "../Core/UniqueIdTable.h"
#include "AssetMetaData.h"
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

  inline const std::string& GetProgramID() const
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
  const URI uri_;
  AssetMetaData* meta_data_;
  std::string program_id_;

};
