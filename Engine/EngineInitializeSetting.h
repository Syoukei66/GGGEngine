#pragma once

#include "NativeType.h"

class EngineInitializeSetting
{
public:
  inline static EngineInitializeSetting& GetInstance()
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
  // setter/getter
  // =================================================================
public:
  inline void SetDefaultLayerId(T_UINT8 id)
  {
    this->default_layer_id_ = id;
  }
  inline T_UINT8 GetDefaultLayerId() const
  {
    return this->default_layer_id_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT8 default_layer_id_;

};