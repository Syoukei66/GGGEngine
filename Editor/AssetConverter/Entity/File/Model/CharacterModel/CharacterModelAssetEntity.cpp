#include "CharacterModelAssetEntity.h"

#include "CharacterModelAssetImporter.h"

IAssetConverter* CharacterModelAssetEntity::CreateConverter()
{
  return FileAssetConverterFactory::Create<CharacterModelAssetEntity>(
    new CharacterModelAssetImporter({ "dae", "blend" }),
    "CharacterModel",
    "rcCharacterModel",
    1,
    1
    );
}
