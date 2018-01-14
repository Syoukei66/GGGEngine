#pragma once

#include "CSVData.h"
#include "FileResource.h"

class CSVResource : public FileResource<CSVData>
{
public:
  static const CSVResource* DynamicLoad(const char* path);

public:
  CSVResource(const char* path);

public:
  virtual CSVData* NativeLoadProcess(const std::string& path) override;

};