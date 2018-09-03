#pragma once

#include "Asset.h"
#include "CsvData.h"

class CsvAsset : public Asset<CsvAsset, rcCsvData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  CsvAsset(const std::string& path)
    : Asset(path)
  {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  rcCsvData* LoadProcess(const std::string& path) override
  {
    return rcCsvData::LoadProcess(path.c_str());
  }

};