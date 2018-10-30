#include "Sound.h"

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcSound> rcSound::CreateFromFile(const char* path)
{
  return NativeProcess::Resource::SoundLoad(path);
}
