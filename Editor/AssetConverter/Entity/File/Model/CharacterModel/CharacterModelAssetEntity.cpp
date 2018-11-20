#include "CharacterModelAssetEntity.h"

#include "CharacterModelAssetImporter.h"

IAssetConverter* CharacterModelAssetEntity::CreateConverter()
{
  return FileAssetConverterFactory::Create<CharacterModelAssetEntity>(
    new CharacterModelAssetImporter({ "x", "fbx", "blend" }),
    "CharacterModel",
    "rcCharacterModel",
    1,
    1
    );
}
