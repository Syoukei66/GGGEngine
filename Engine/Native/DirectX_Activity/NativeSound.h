#pragma once

#include <XAudio2.h>
#include <NativeSound.h>

class NativeSound : public INativeSound
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeSound(const char* path);
  ~NativeSound();

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Play(T_UINT8 loop_count = 0) override;
  virtual void Stop() override;
  virtual void Pause() override;
  virtual void Resume() override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  IXAudio2SourceVoice* souce_voice_;
  BYTE* data_audio_;
  DWORD size_audio_;
};