#pragma once

#include "SpineData.h"
#include "FileResource.h"

class SpineResource : public FileResource<SpineData>
{
public:
  static SpineResource* DynamicLoad(const char* path);

public:
  SpineResource(const char* path);

public:
  virtual SpineData* NativeLoadProcess(const std::string& path) override;
};