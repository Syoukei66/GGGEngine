#pragma once

class AssetInfo;

namespace Logger
{
void SkipAssetLog(const AssetInfo* info);
void ConvertAssetLog(const AssetInfo* info);
void CopyAssetLog(const AssetInfo* info);
};