#include "EngineInputEvent.h"

// =================================================================
// Constructor / Destructor
// =================================================================
EngineInputState::EngineInputState()
  : analog_input_()
  , digital_input_()
{}

// =================================================================
// Method
// =================================================================
void EngineInputState::Prepare()
{
  for (std::unordered_map<T_UINT8, AnalogInputState>::iterator itr = this->analog_input_.begin(), end = this->analog_input_.end(); itr != end; ++itr)
  {
    (*itr).second.Prepare();
  }
  for (std::unordered_map<T_UINT8, DigitalInputState>::iterator itr = this->digital_input_.begin(), end = this->digital_input_.end(); itr != end; ++itr)
  {
    (*itr).second.Prepare();
  }
}

void EngineInputState::PreInputAnalog(T_UINT8 handler, EngineInput::Analog::ID id)
{
  this->analog_input_[handler].PreInput(id);
}

void EngineInputState::InputAnalog(T_UINT8 handler, EngineInput::Analog::ID id, T_UINT8 dimension, T_FLOAT value)
{
  this->analog_input_[handler].InputValue(id, dimension, value);
}

void EngineInputState::PostInputAnalog(T_UINT8 handler, EngineInput::Analog::ID id)
{
  this->analog_input_[handler].PostInput(id);
}

void EngineInputState::PreInputDigital(T_UINT8 handler, EngineInput::Digital::ID id)
{
  this->digital_input_[handler].PreInput(id);
}

void EngineInputState::InputDigital(T_UINT8 handler, EngineInput::Digital::ID id)
{
  this->digital_input_[handler].InputValue(id);
}

void EngineInputState::PostInputDigital(T_UINT8 handler, EngineInput::Digital::ID id)
{
  this->digital_input_[handler].PostInput(id);
}



