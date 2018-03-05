#pragma once
#include <string>
#include "NativeTexture.h"
#include "FileResource.h"
#include "NativeSound.h"

class SoundResource : public FileResource<INativeSound>
{
public:
  static SoundResource* DynamicLoad(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  SoundResource(const char* path);

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual INativeSound* NativeLoadProcess(const std::string& path) override;
  inline void Play(T_UINT8 loop_count = 0)
  {
    return this->GetContents()->Play(loop_count);
  }
  inline void Stop()
  {
    return this->GetContents()->Stop();
  }
  inline void Pause()
  {
    return this->GetContents()->Pause();
  }
  inline void Resume()
  {
    return this->GetContents()->Resume();
  }

};
