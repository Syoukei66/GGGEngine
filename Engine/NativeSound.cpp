#include "NativeSound.h"
#include "NativeObjectFactory.h"

INativeSound* INativeSound::Create(const char* path)
{
  return NativeObjectFactory::CreateSound(path);
}
