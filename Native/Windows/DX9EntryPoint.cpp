#include "DX9EntryPoint.h"

#define GG_GRAPHICS_API_DX9

#include <Native/Windows/WindowsActivity.h>
#include <Native/Windows/API/Audio/XAudio/XAudioAPI.h>
#include <Native/Windows/API/Graphics/DX9/DX9GraphicsAPI.h>
#include <Native/Windows/API/Input/DirectInput/DirectInputAPI.h>

// =================================================================
// Methods from IPlatformSetting
// =================================================================
UniqueRef<Activity> DX9EntryPoint::CreateActivity(const ActivityOption& option) const
{
  return UniqueRef<Activity>();
}

UniqueRef<GraphicsAPI> DX9EntryPoint::CreateGraphicsAPI() const
{
  return DX9GraphicsAPI::Create();
}

UniqueRef<AudioAPI> DX9EntryPoint::CreateAudioAPI() const
{
  return XAudioAPI::Create();
}

UniqueRef<InputAPI> DX9EntryPoint::CreateInputAPI(const InputSetting& setting) const
{
  return DirectInputAPI::Create(setting);
}
