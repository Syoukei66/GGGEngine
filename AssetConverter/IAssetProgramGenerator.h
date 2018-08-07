#pragma once

#include <string>

#include "AssetInfo.h"

namespace AssetProgram
{

class IProgramGenerator
{
public:
  virtual std::string CreateHeaderProgram(AssetInfo* info) const = 0;
  virtual std::string CreateCppProgram(AssetInfo* info) const = 0;
};

}