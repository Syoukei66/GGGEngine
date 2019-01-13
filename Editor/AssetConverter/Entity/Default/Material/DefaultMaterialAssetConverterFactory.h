#pragma once

class AssetConverter;
class AssetConverterContext;

namespace DefaultMaterialAssetConverterFactory
{
AssetConverter* Create(AssetConverterContext* context);
}
