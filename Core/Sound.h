#pragma once

#include "Resource.h"

class rcSound : public Resource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueResource<rcSound> CreateFromFile(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcSound() {}
  virtual ~rcSound() {}

  // =================================================================
  // Getter / Setter
  // =================================================================
public:
  inline virtual const char* GetResourceName() override
  {
    return "Sound";
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void Play(T_UINT8 loop_count = 0) = 0;
  virtual void Stop() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;

};