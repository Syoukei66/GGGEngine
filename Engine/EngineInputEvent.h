#ifndef HAL_ENGINE_SCENE_EVENT_ENGINEINPUT_ENGINEINPUTEVENT_H_
#define HAL_ENGINE_SCENE_EVENT_ENGINEINPUT_ENGINEINPUTEVENT_H_

#include <unordered_map>
#include "NativeType.h"
#include "AnalogInput.h"
#include "DigitalInput.h"
#include "EngineInput.h"

class EngineInputState
{
public:
  static EngineInputState* GetInstance()
  {
    static EngineInputState self;
    return &self;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  EngineInputState();

  // =================================================================
  // Method
  // =================================================================
public:
  void Prepare();
  void PreInputAnalog(T_UINT8 handler, EngineInput::Analog::ID id);
  void InputAnalog(T_UINT8 handler, EngineInput::Analog::ID id, T_UINT8 dimension, T_FLOAT value);
  void PostInputAnalog(T_UINT8 handler, EngineInput::Analog::ID id);
  void PreInputDigital(T_UINT8 handler, EngineInput::Digital::ID id);
  void InputDigital(T_UINT8 handler, EngineInput::Digital::ID id);
  void PostInputDigital(T_UINT8 handler, EngineInput::Digital::ID id);

  // =================================================================
  // Setter/Getter
  // =================================================================
public:
  inline const AnalogInputState* GetAnalogInput(T_UINT8 handler) const
  {
    if (this->analog_input_.find(handler) == this->analog_input_.end())
    {
      return &AnalogInputState::NULL_INPUT;
    }
    return &(this->analog_input_.at(handler));
  }
  
  inline const DigitalInputState* GetDigitalInput(T_UINT8 handler) const
  {
    if (this->digital_input_.find(handler) == this->digital_input_.end())
    {
      return &DigitalInputState::NULL_INPUT;
    }
    return &(this->digital_input_.at(handler));
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::unordered_map<T_UINT8, AnalogInputState> analog_input_;
  std::unordered_map<T_UINT8, DigitalInputState> digital_input_;
};

#endif//HAL_ENGINE_SCENE_EVENT_ENGINEINPUT_ENGINEINPUTEVENT_H_
