#pragma once

#include <string>
#include "AssetInfo.h"
#include "Setting.h"

namespace Logger
{
void SkipAssetLog(const Setting* setting, const AssetInfo* info);
void ConvertAssetLog(const Setting* setting, const AssetInfo* info);
void CopyAssetLog(const Setting* setting, const AssetInfo* info);
};