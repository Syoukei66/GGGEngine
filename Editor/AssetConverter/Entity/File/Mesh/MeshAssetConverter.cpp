#include "MeshAssetConverter.h"

// =================================================================
// Methods from AssetConverter
// =================================================================
IAssetDataContainer* MeshAssetConverter::ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext * context) const
{
  return entity->GetDataContainer();
}
