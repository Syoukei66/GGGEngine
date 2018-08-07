#pragma once

namespace Assimp
{
class Importer;
}

#include "BaseConverter.h"

class StaticModelConverter : public BaseConverter
{
public:
  StaticModelConverter();
  ~StaticModelConverter();
  
public:
  void GetIncludePaths(std::set<std::string>* dest) const override;
  bool IsTarget(const std::string& extension) const override;

protected:
  void ConvertProcess(AssetInfo* info) const override;

private:
  Assimp::Importer* const importer_;

};