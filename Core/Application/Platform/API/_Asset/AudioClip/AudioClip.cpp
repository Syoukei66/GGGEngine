#include "AudioClip.h"

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcAudioClip> rcAudioClip::CreateFromFile(const char* path)
{
  return Application::GetPlatform()->GetAudioAPI()->LoadSound(path);
}
