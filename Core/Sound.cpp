#include "Sound.h"
#include "NativeProcess.h"

// =================================================================
// Factory Method
// =================================================================
UniqueResource<rcSound> rcSound::CreateFromFile(const char* path)
{
  UniqueResource<rcSound> ret = NativeProcess::Resource::SoundLoad(path);
  ret->Resource::Init();
  return ret;
}
