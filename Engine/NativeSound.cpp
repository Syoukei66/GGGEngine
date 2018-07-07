#include "NativeSound.h"
#include "NativeProcess.h"

INativeSound* INativeSound::Create(const char* path)
{
  return NativeProcess::Factory::CreateSound(path);
}
