#pragma once

#include "Asset.h"
#include "CsvData.h"

class CsvAsset : public BaseAsset<CsvAsset, rcCsvData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  CsvAsset(const std::string& path)
    : BaseAsset(path)
  {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  rcCsvData* LoadProcess(const std::string& path) override
  {
    return rcCsvData::CreateFromFile(path.c_str());
  }

};