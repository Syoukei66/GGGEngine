#pragma once

#include <string>
#include "AssetInfo.h"

namespace Logger
{
void SkipAssetLog(const AssetInfo* info);
void ConvertAssetLog(const AssetInfo* info);
void CopyAssetLog(const AssetInfo* info);
};