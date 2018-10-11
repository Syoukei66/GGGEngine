#pragma once

class IAssetConverter;
class AssetConverterContext;

namespace DefaultMaterialAssetConverterFactory
{
IAssetConverter* Create(AssetConverterContext* context);
}
