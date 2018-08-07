#pragma once

#include "../Asset/ModelConstants.h"
#include "../Common/NativeType.h"

enum aiBlendMode;
enum aiShadingMode;
enum aiTextureFlags;
enum aiTextureMapMode;
enum aiTextureMapping;
enum aiTextureOp;
enum aiTextureType;

namespace ModelImporter
{

namespace Assimp
{

ModelConstants::BlendMode ConvertBlendMode(aiBlendMode mode);
ModelConstants::ShadingMode ConvertShadingMode(aiShadingMode mode);
T_UINT8 ConvertTextureFlags(T_UINT32 flags);
ModelConstants::TextureMapMode ConvertTextureMapMode(aiTextureMapMode mode);
ModelConstants::TextureMapping ConvertTextureMapping(aiTextureMapping mapping);
ModelConstants::TextureOp ConvertTextureOp(aiTextureOp op);
ModelConstants::TextureType ConvertTextureType(aiTextureType type);

struct TextureDatas
{
  ModelConstants::TextureType type;
  T_UINT8 count;
  T_UINT32* ids;
};

} // namespace Assimp

} // namespace ModelImporter