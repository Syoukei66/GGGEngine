#pragma once

#include "URI.h"

class AssetConverterContext;
class AssetInfo;
class AssetEntity;

class IAssetConverter
{
public:
  virtual ~IAssetConverter() {}

public:
  virtual T_UINT32 GetID() const = 0;
  virtual bool Reserve(const URI& uri, AssetConverterContext* context) = 0;
  virtual void Import(AssetConverterContext* context) = 0;
  virtual bool ImportOnce(AssetConverterContext* context) = 0;
  virtual void Export(const AssetConverterContext* context) const = 0;
  virtual void CreateHeaderProgram(std::string* dest) const = 0;
  virtual void CreateCppProgram(std::string* dest) const = 0;
  virtual void VisitAllEntity(const std::function<void(AssetEntity*)>& func) = 0;
};