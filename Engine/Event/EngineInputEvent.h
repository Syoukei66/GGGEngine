#pragma once

#include "AnalogInput.h"
#include "DigitalInput.h"
#include "EngineInput.h"

class EngineInputState
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(EngineInputState);

  // =================================================================
  // Method
  // =================================================================
public:
  static void Prepare();
  static void PreInputAnalog(T_UINT8 handler, EngineInput::Analog::ID id);
  static void InputAnalog(T_UINT8 handler, EngineInput::Analog::ID id, T_UINT8 dimension, T_FLOAT value);
  static void PostInputAnalog(T_UINT8 handler, EngineInput::Analog::ID id);
  static void PreInputDigital(T_UINT8 handler, EngineInput::Digital::ID id);
  static void InputDigital(T_UINT8 handler, EngineInput::Digital::ID id);
  static void PostInputDigital(T_UINT8 handler, EngineInput::Digital::ID id);

  // =================================================================
  // Setter/Getter
  // =================================================================
public:
  static GG_INLINE const AnalogInputState* GetAnalogInput(T_UINT8 handler)
  {
    if (Self().analog_input_.find(handler) == Self().analog_input_.end())
    {
      return &AnalogInputState::NULL_INPUT;
    }
    return &(Self().analog_input_.at(handler));
  }
  
  static GG_INLINE const DigitalInputState* GetDigitalInput(T_UINT8 handler)
  {
    if (Self().digital_input_.find(handler) == Self().digital_input_.end())
    {
      return &DigitalInputState::NULL_INPUT;
    }
    return &(Self().digital_input_.at(handler));
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::unordered_map<T_UINT8, AnalogInputState> analog_input_;
  std::unordered_map<T_UINT8, DigitalInputState> digital_input_;
};
