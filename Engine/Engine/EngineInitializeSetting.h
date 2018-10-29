#pragma once

#include <Core/NativeType.h>

class EngineInitializeSetting
{
public:
  GG_INLINE static EngineInitializeSetting& GetInstance()
  {
    static EngineInitializeSetting self = EngineInitializeSetting();
    return self;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  EngineInitializeSetting();

  // =================================================================
  // Method
  // =================================================================
public:


  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE void SetDefaultLayerId(T_UINT8 id)
  {
    this->default_layer_id_ = id;
  }
  GG_INLINE T_UINT8 GetDefaultLayerId() const
  {
    return this->default_layer_id_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT8 default_layer_id_;

};