#include "NativeRenderTexture.h"

#include "NativeObjectFactory.h"

INativeRenderTexture* INativeRenderTexture::Create(T_UINT16 width, T_UINT16 height)
{
  return NativeObjectFactory::CreateDynamicTexture(width, height);
}
