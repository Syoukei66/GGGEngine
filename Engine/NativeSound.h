#pragma once

#include "NativeObject.h"
#include "Geometry.h"

struct NativeSoundInstance { void* p; };

class INativeSound : public NativeObject<NativeSoundInstance>
{
  // =================================================================
  // Static Method
  // =================================================================
public:
  static INativeSound* Create(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  INativeSound(NativeSoundInstance* instance)
    : NativeObject(instance)
  {}
  virtual ~INativeSound() {}

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void Play(T_UINT8 loop_count = 0) = 0;
  virtual void Stop() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;

};