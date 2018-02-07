#include "AnalogInput.h"
#include <algorithm>
#include "NativeAssert.h"

const AnalogInputState AnalogInputState::NULL_INPUT = AnalogInputState();

// =================================================================
// Constructor / Destructor
// =================================================================
AnalogInputState::AnalogInputState()
{
  for (T_UINT8 i = 0; i < EngineInput::Analog::ID_ANALOG_MAX; ++i)
  {
    for (T_UINT8 j = 0; j < EngineInput::Analog::DIMENSION_DATANUM; ++j)
    {
      this->old_input_[i][j] = 0.0f;
      this->input_[i][j] = 0.0f;
    }
  }
}

// =================================================================
// Method
// =================================================================
void AnalogInputState::Prepare()
{
  for (T_UINT8 i = 0; i < EngineInput::Analog::ID_ANALOG_MAX; ++i)
  {
    this->input_prepared_[i] = false;
  }
}

void AnalogInputState::PreInput(EngineInput::Analog::ID id)
{
  if (this->input_prepared_[id])
  {
    return;
  }
  this->input_prepared_[id] = true;
  for (T_UINT8 j = 0; j < EngineInput::Analog::DIMENSION_DATANUM; ++j)
  {
    this->old_input_[id][j] = this->input_[id][j];
    this->input_[id][j] = 0.0f;
  }
}

void AnalogInputState::InputValue(EngineInput::Analog::ID id, T_UINT8 dimension, T_FLOAT value)
{
  NATIVE_ASSERT(this->input_prepared_[id], "AnalogInput:: デバイスの入力処理の前にPrepareInputが呼び出されていません。");
  this->input_[id][dimension] = std::min(1.0f, std::max(-1.0f, value));
}

void AnalogInputState::PostInput(EngineInput::Analog::ID id)
{
}

