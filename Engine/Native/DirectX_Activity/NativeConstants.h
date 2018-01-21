#pragma once

#include <d3d9.h>
#include "INativeProcess_Graphics.h"


namespace NativeConstants
{

static const DWORD FVF_TYPES[INativeProcess_Graphics::VERTEX_TYPE_DATANUM] =
{
  D3DFVF_XYZW | D3DFVF_DIFFUSE,
  D3DFVF_XYZW | D3DFVF_DIFFUSE | D3DFVF_TEX1,
  D3DFVF_XYZW | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL,
};

static const T_UINT32 VERTEX_SIZE[INativeProcess_Graphics::VERTEX_TYPE_DATANUM] =
{
  sizeof(Vertex),
  sizeof(SpriteVertex),
  sizeof(Vertex3D),
};

static const D3DPRIMITIVETYPE PRIMITIVE_TYPES[INativeProcess_Graphics::PRIMITIVE_DATANUM] =
{
  D3DPT_POINTLIST,
  D3DPT_LINELIST,
  D3DPT_LINESTRIP,
  D3DPT_TRIANGLELIST,
  D3DPT_TRIANGLESTRIP,
  D3DPT_TRIANGLEFAN,
};

static int PRIMITIVE_SURF_NUM(INativeProcess_Graphics::PrimitiveType type, int num)
{
  if (type == INativeProcess_Graphics::PRIMITIVE_POINTS)
  {
    return num;
  }
  if (type == INativeProcess_Graphics::PRIMITIVE_LINES)
  {
    return num;
  }
  if (type == INativeProcess_Graphics::PRIMITIVE_LINESTRIP)
  {
    return num;
  }
  if (type == INativeProcess_Graphics::PRIMITIVE_TRIANGLES)
  {
    return num / 3;
  }
  if (type == INativeProcess_Graphics::PRIMITIVE_TRIANGLESTRIP)
  {
    return num - 2;
  }
  if (type == INativeProcess_Graphics::PRIMITIVE_TRIANGLEFAN)
  {
    return num - 2;
  }
  return num;
}

}