#pragma once

namespace ModelConstants
{
//http://sir-kimmi.de/assimp/lib_html/material_8h.html#ae1236da1ccfbf4f23bb490287a4d61ac
enum BlendMode
{
  BLEND_MODE_DEFAULT,
  BLEND_MODE_ADD,

  BLEND_MODE_DATANUM
};

//http://sir-kimmi.de/assimp/lib_html/material_8h.html#a93e23e0201d6ed86fb4287e15218e4cf
enum ShadingMode
{
  SHADING_MODE_FLAT,
  SHADING_MODE_GOURAUD,
  SHADING_MODE_PHONG,
  SHADING_MODE_BLINN,
  SHADING_MODE_TOON,
  SHADING_MODE_OREN_NAYER,
  SHADING_MODE_MINNAERT,
  SHADING_MODE_COOK_TORRANCE,
  SHADING_MODE_NO_SHADING,
  SHADING_MODE_FRESNEL,

  SHADING_MODE_DATANUM
};

//http://sir-kimmi.de/assimp/lib_html/material_8h.html#a6d003e078617e4e80d1313a6250b2dfd
enum TextureFlags
{
  TEX_FLAG_INVERT,
  TEX_FLAG_USE_ALPHA,
  TEX_FLAG_IGNORE_ALPHA,
  
  TEX_FLAG_DATANUM,
};

//http://sir-kimmi.de/assimp/lib_html/material_8h.html#a6cbe56056751aa80e8dd714632a49de0
enum TextureMapMode
{
  TEX_MAP_MODE_WRAP,
  TEX_MAP_MODE_CLAMP,
  TEX_MAP_MODE_MIRROR,
  TEX_MAP_MODE_DECAL,

  TEX_MAP_MODE_DATANUM,
};

//http://sir-kimmi.de/assimp/lib_html/material_8h.html#a6cbe56056751aa80e8dd714632a49de0
enum TextureMapping
{
  TEX_MAPPING_UV,
  TEX_MAPPING_SPHERE,
  TEX_MAPPING_CYLINDER,
  TEX_MAPPING_BOX,
  TEX_MAPPING_PLANE,
  TEX_MAPPING_OTHER,

  TEX_MAPPING_DATANUM,
};

//http://sir-kimmi.de/assimp/lib_html/material_8h.html#afcd3096d69affba13114cedfc6f9ee6b
enum TextureOp
{
  TEX_OP_MUL,
  TEX_OP_ADD,
  TEX_OP_SUB,
  TEX_OP_DIV,
  TEX_OP_SMOOTH_ADD,
  TEX_OP_SIGNED_ADD,

  TEX_OP_DATANUM,
};

//http://sir-kimmi.de/assimp/lib_html/material_8h.html#a7dd415ff703a2cc53d1c22ddbbd7dde0
enum TextureType
{
  TEX_TYPE_NONE,
  TEX_TYPE_DIFFUSE,
  TEX_TYPE_SPECULAR,
  TEX_TYPE_AMBIENT,
  TEX_TYPE_EMISSIVE,
  TEX_TYPE_HEIGHT,
  TEX_TYPE_NORMALS,
  TEX_TYPE_SHININESS,
  TEX_TYPE_OPACITY,
  TEX_TYPE_DISPLACEMENT,
  TEX_TYPE_AMBIENT_OCCLUSION,
  TEX_TYPE_REFLECTION,
  TEX_TYPE_UNKNOWN,

  TEX_TYPE_DATANUM,
};

//http://sir-kimmi.de/assimp/lib_html/materials.html#General
enum ColorType
{
  COL_TYPE_DIFFUSE,
  COL_TYPE_SPECULAR,
  COL_TYPE_AMBIENT,
  COL_TYPE_EMISSIVE,
  COL_TYPE_TRANSPARENT,

  COL_TYPE_DATANUM,
};

}