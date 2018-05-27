#pragma once

#include <d3d9.h>
#include "INativeProcess_Graphics.h"


namespace NativeConstants
{

static const D3DPRIMITIVETYPE PRIMITIVE_TYPES[GraphicsConstants::PRIMITIVE_DATANUM] =
{
  D3DPT_POINTLIST,
  D3DPT_LINELIST,
  D3DPT_LINESTRIP,
  D3DPT_TRIANGLELIST,
  D3DPT_TRIANGLESTRIP,
  D3DPT_TRIANGLEFAN,
};

}