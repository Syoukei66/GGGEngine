#pragma once

#include "FileResource.h"
#include "JsonData.h"

class JsonResource : public FileResource<JsonData>
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static JsonResource* DynamicLoad(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  JsonResource(const char* path);
  ~JsonResource();

  // =================================================================
  // Methods for/from interface/super class
  // =================================================================
private:
  virtual JsonData* NativeLoadProcess(const std::string& path) override;

};