#pragma once

#include "Resource.h"

class rcSound : public Resource
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  static rcSound* Create(const char* path);

protected:
  rcSound() {}
  virtual ~rcSound() {}

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void Play(T_UINT8 loop_count = 0) = 0;
  virtual void Stop() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;

};