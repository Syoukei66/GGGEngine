#pragma once

#include "Asset.h"
#include "JsonData.h"

class JsonAsset : public Asset<JsonAsset, rcJsonData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  JsonAsset(const std::string& path)
    : Asset(path)
  {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  rcJsonData* LoadProcess(const std::string& path) override
  {
    return rcJsonData::LoadProcess(path.c_str());
  }

};