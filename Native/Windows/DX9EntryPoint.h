#pragma once

#include <Engine/EntryPoint.h>

class DX9EntryPoint : public EntryPoint
{
  // =================================================================
  // Methods from IPlatformSetting
  // =================================================================
public:
  virtual UniqueRef<Activity> CreateActivity(const ActivityOption & option) const override;
  virtual UniqueRef<GraphicsAPI> CreateGraphicsAPI() const override;
  virtual UniqueRef<AudioAPI> CreateAudioAPI() const override;
  virtual UniqueRef<InputAPI> CreateInputAPI(const InputSetting& setting) const override;

};