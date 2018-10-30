//#include "AssimpMaterialSystemImporter.h"
//
//#include <assimp\scene.h>
//
//namespace ModelAssetImporter
//{
//
//namespace Assimp
//{
//
//ModelConstants::BlendMode ConvertBlendMode(aiBlendMode mode)
//{
//  using namespace ModelConstants;
//  switch (mode)
//  {
//  case aiBlendMode_Default:
//    return BLEND_MODE_DEFAULT;
//
//  case aiBlendMode_Additive:
//    return BLEND_MODE_ADD;
//  }
//  return BLEND_MODE_DATANUM;
//}
//
//ModelConstants::ShadingMode ConvertShadingMode(aiShadingMode mode)
//{
//  using namespace ModelConstants;
//  switch (mode)
//  {
//  case aiShadingMode_Flat:
//    return SHADING_MODE_FLAT;
//
//  case aiShadingMode_Gouraud:
//    return SHADING_MODE_GOURAUD;
//
//  case aiShadingMode_Phong:
//    return SHADING_MODE_PHONG;
//
//  case aiShadingMode_Blinn:
//    return SHADING_MODE_BLINN;
//
//  case aiShadingMode_Toon:
//    return SHADING_MODE_TOON;
//
//  case aiShadingMode_OrenNayar:
//    return SHADING_MODE_OREN_NAYER;
//
//  case aiShadingMode_Minnaert:
//    return SHADING_MODE_MINNAERT;
//
//  case aiShadingMode_CookTorrance:
//    return SHADING_MODE_COOK_TORRANCE;
//
//  case aiShadingMode_NoShading:
//    return SHADING_MODE_NO_SHADING;
//
//  case aiShadingMode_Fresnel:
//    return SHADING_MODE_FRESNEL;
//  }
//  return SHADING_MODE_DATANUM;
//}
//
//T_UINT8 ConvertTextureFlags(T_UINT32 flags)
//{
//  using namespace ModelConstants;
// 
//  T_UINT8 ret = 0;
//  if (flags & aiTextureFlags_Invert)
//  {
//    ret |= 1 << TEX_FLAG_INVERT;
//  }
//  if (flags & aiTextureFlags_UseAlpha)
//  {
//    ret |= 1 << TEX_FLAG_USE_ALPHA;
//  }
//  if (flags & aiTextureFlags_IgnoreAlpha)
//  {
//    ret |= 1 << TEX_FLAG_IGNORE_ALPHA;
//  }
//  return ret;
//}
//
//ModelConstants::TextureMapMode ConvertTextureMapMode(aiTextureMapMode mode)
//{
//  using namespace ModelConstants;
//  switch (mode)
//  {
//  case aiTextureMapMode_Wrap:
//    return TEX_MAP_MODE_WRAP;
//
//  case aiTextureMapMode_Clamp:
//    return TEX_MAP_MODE_CLAMP;
//
//  case aiTextureMapMode_Mirror:
//    return TEX_MAP_MODE_MIRROR;
//
//  case aiTextureMapMode_Decal:
//    return TEX_MAP_MODE_DECAL;
//
//  }
//  return TEX_MAP_MODE_DATANUM;
//}
//
//ModelConstants::TextureMapping ConvertTextureMapping(aiTextureMapping mapping)
//{
//  using namespace ModelConstants;
//
//  switch (mapping)
//  {
//  case aiTextureMapping_UV:
//    return TEX_MAPPING_UV;
//
//  case aiTextureMapping_SPHERE:
//    return TEX_MAPPING_SPHERE;
//
//  case aiTextureMapping_CYLINDER:
//    return TEX_MAPPING_CYLINDER;
//
//  case aiTextureMapping_BOX:
//    return TEX_MAPPING_BOX;
//
//  case aiTextureMapping_PLANE:
//    return TEX_MAPPING_PLANE;
//
//  case aiTextureMapping_OTHER:
//    return TEX_MAPPING_OTHER;
//  }
//
//  return TEX_MAPPING_DATANUM;
//}
//
//ModelConstants::TextureOp ConvertTextureOp(aiTextureOp op)
//{
//  using namespace ModelConstants;
//
//  switch (op)
//  {
//  case aiTextureOp_Multiply:
//    return TEX_OP_MUL;
//
//  case aiTextureOp_Add:
//    return TEX_OP_ADD;
//
//  case aiTextureOp_Subtract:
//    return TEX_OP_SUB;
//
//  case aiTextureOp_Divide:
//    return TEX_OP_DIV;
//
//  case aiTextureOp_SmoothAdd:
//    return TEX_OP_SMOOTH_ADD;
//
//  case aiTextureOp_SignedAdd:
//    return TEX_OP_SIGNED_ADD;
//  }
//
//  return TEX_OP_DATANUM;
//}
//
//ModelConstants::TextureType ConvertTextureType(aiTextureType type)
//{
//  using namespace ModelConstants;
//
//  switch (type)
//  {
//  case aiTextureType_NONE:
//    return TEX_TYPE_NONE;
//
//  case aiTextureType_DIFFUSE:
//    return TEX_TYPE_DIFFUSE;
//
//  case aiTextureType_SPECULAR:
//    return TEX_TYPE_SPECULAR;
//
//  case aiTextureType_AMBIENT:
//    return TEX_TYPE_AMBIENT;
//
//  case aiTextureType_EMISSIVE:
//    return TEX_TYPE_EMISSIVE;
//
//  case aiTextureType_HEIGHT:
//    return TEX_TYPE_HEIGHT;
//
//  case aiTextureType_NORMALS:
//    return TEX_TYPE_NORMALS;
//
//  case aiTextureType_SHININESS:
//    return TEX_TYPE_SHININESS;
//
//  case aiTextureType_OPACITY:
//    return TEX_TYPE_OPACITY;
//
//  case aiTextureType_DISPLACEMENT:
//    return TEX_TYPE_DISPLACEMENT;
//
//  case aiTextureType_LIGHTMAP:
//    return TEX_TYPE_AMBIENT_OCCLUSION;
//
//  case aiTextureType_REFLECTION:
//    return TEX_TYPE_REFLECTION;
//
//  case aiTextureType_UNKNOWN:
//    return TEX_TYPE_UNKNOWN;
//  }
//
//  return TEX_TYPE_DATANUM;
//}
//
//
//} // namespace Assimp
//
//} // namespace ModelImporter