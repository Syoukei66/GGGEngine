#pragma once

#include "Asset.h"
#include "JsonData.h"

class JsonAsset : public BaseAsset<JsonAsset, rcJsonData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  JsonAsset(const std::string& path)
    : BaseAsset(path)
  {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  rcJsonData* LoadProcess(const std::string& path) override
  {
    return rcJsonData::CreateFromFile(path.c_str());
  }

};