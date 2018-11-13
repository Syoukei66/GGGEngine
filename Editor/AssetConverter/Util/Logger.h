#pragma once

class AssetInfo;
class URI;

namespace Logger
{
void ImportAssetLog(const URI& uri);
void ImportSkipAssetLog(const URI& uri);

void CommitAssetLog(const AssetInfo* info);

void ConvertAssetLog(const AssetInfo* info);
void CopyAssetLog(const AssetInfo* info);
void ExportSkipAssetLog(const AssetInfo* info);
};