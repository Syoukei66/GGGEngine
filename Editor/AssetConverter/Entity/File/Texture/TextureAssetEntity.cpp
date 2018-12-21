#include "TextureAssetEntity.h"
#include "TextureAssetImporter.h"

IAssetConverter* TextureAssetEntity::CreateConverter()
{
  return FileAssetConverterFactory::Create<TextureAssetEntity>(
    new TextureAssetImporter({ "jpg", "png", "tga", "bmp", "jpeg" }),
    "Texture",
    "rcTexture",
    1,
    1
    );
}
