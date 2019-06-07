#pragma once

#include "AnalogInput.h"
#include "DigitalInput.h"
#include "EngineInput.h"

class EngineInputState
{
  // =================================================================
  // Methods
  // =================================================================
public:
  void Prepare();
  
  GG_INLINE void PreInputAnalog(T_UINT8 handler, EngineInput::Analog::ID id)
  {
    this->analog_input_[handler].PreInput(id);
  }
  GG_INLINE void InputAnalog(T_UINT8 handler, EngineInput::Analog::ID id, T_UINT8 dimension, T_FLOAT value)
  {
    this->analog_input_[handler].InputValue(id, dimension, value);
  }
  GG_INLINE void PostInputAnalog(T_UINT8 handler, EngineInput::Analog::ID id)
  {
    this->analog_input_[handler].PostInput(id);
  }
  
  GG_INLINE void PreInputDigital(T_UINT8 handler, EngineInput::Digital::ID id)
  {
    this->digital_input_[handler].PreInput(id);
  }
  GG_INLINE void InputDigital(T_UINT8 handler, EngineInput::Digital::ID id)
  {
    this->digital_input_[handler].InputValue(id);
  }
  GG_INLINE void PostInputDigital(T_UINT8 handler, EngineInput::Digital::ID id)
  {
    this->digital_input_[handler].PostInput(id);
  }

  // =================================================================
  // Setter/Getter
  // =================================================================
public:
  GG_INLINE const AnalogInputState& GetAnalogInput(T_UINT8 handler) const
  {
    const auto& itr = this->analog_input_.find(handler);
    if (itr == this->analog_input_.end())
    {
      return AnalogInputState::NULL_INPUT;
    }
    return itr->second;
  }
  
  GG_INLINE const DigitalInputState& GetDigitalInput(T_UINT8 handler) const
  {
    const auto& itr = this->digital_input_.find(handler);
    if (itr == this->digital_input_.end())
    {
      return DigitalInputState::NULL_INPUT;
    }
    return itr->second;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::unordered_map<T_UINT8, AnalogInputState> analog_input_;
  std::unordered_map<T_UINT8, DigitalInputState> digital_input_;

};
