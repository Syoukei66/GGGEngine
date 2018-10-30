#pragma once

class EngineInitializeSetting
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(EngineInitializeSetting);
  
  // =================================================================
  // Methods
  // =================================================================
public:
  void Load();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  static GG_INLINE void SetDefaultLayerId(T_UINT8 id)
  {
    Self().default_layer_id_ = id;
  }
  static GG_INLINE T_UINT8 GetDefaultLayerId()
  {
    return Self().default_layer_id_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT8 default_layer_id_;

};