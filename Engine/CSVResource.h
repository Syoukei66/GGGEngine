#pragma once

#include "CSVData.h"
#include "FileResource.h"

class CSVResource : public FileResource<CSVData>
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static CSVResource* DynamicLoad(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  CSVResource(const char* path);

  // =================================================================
  // Methods for/from interface/super class
  // =================================================================
public:
  virtual CSVData* NativeLoadProcess(const std::string& path) override;

};