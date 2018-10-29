#include "Sound.h"
#include "NativeProcess.h"

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcSound> rcSound::CreateFromFile(const char* path)
{
  UniqueRef<rcSound> ret = NativeProcess::GGAssetObject::SoundLoad(path);
  ret->GGAssetObject::Init();
  return ret;
}
