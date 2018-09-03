#include "Sound.h"
#include "NativeProcess.h"

// =================================================================
// Factory Method
// =================================================================
rcSound* rcSound::CreateFromFile(const char* path)
{
  rcSound* ret = NativeProcess::Resource::SoundLoad(path);
  ret->Resource::Init();
  return ret;
}
