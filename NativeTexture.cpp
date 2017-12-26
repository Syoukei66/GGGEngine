#include "NativeTexture.h"

#include "NativeObjectFactory.h"

INativeTexture* INativeTexture::Create(const char* path)
{
  return NativeObjectFactory::CreateTexture(path);
}
