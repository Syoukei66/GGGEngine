#pragma once

#include <string>
#include "../Core/NativeType.h"

class AssetConverterContext;
class AssetInfo;

class IAssetConverter
{
public:
  virtual T_UINT32 GetID() const = 0;
  virtual AssetInfo* Reserve(const std::string& directory_path, const std::string& file_name, const std::string& extension, AssetConverterContext* context) = 0;
  virtual void Import(AssetConverterContext* context) = 0;
  virtual bool ImportOnce(AssetConverterContext* context) = 0;
  virtual void Export(const AssetConverterContext* context) const = 0;
  virtual void CreateHeaderProgram(std::string* dest) const = 0;
  virtual void CreateCppProgram(std::string* dest) const = 0;
};