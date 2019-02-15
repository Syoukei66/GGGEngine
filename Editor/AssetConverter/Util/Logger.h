#pragma once

class AssetMetaData;
class URI;

namespace Logger
{
void ImportAssetLog(const URI& uri);
void ImportFromCacheAssetLog(const URI& uri);
void ImportSkipAssetLog(const URI& uri);

void CommitAssetLog(const AssetMetaData* meta);

void ConvertAssetLog(const AssetMetaData* meta);
void ConvertFaildLog(const AssetMetaData* meta);
void CopyAssetLog(const AssetMetaData* meta);
void ExportSkipAssetLog(const AssetMetaData* meta);
};