#include "Sound.h"
#include "NativeProcess.h"

// =================================================================
// Constructor / Destructor
// =================================================================
rcSound* rcSound::Create(const char* path)
{
  rcSound* ret = NativeProcess::Resource::SoundLoad(path);
  ret->Resource::Init();
  return ret;
}
