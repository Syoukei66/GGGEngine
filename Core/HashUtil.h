#pragma once

#include <string>

#include "NativeType.h"

namespace Util
{

namespace Hash
{

inline T_UINT32 GetHash(const std::string& path)
{
  return (T_UINT32)std::hash<std::string>()(path);
}

}

}