#include "DigitalInput.h"
#include "NativeAssert.h"

const DigitalInputState DigitalInputState::NULL_INPUT = DigitalInputState();

// =================================================================
// Constructor / Destructor
// =================================================================
DigitalInputState::DigitalInputState()
  : old_state_(0)
  , now_state_(0)
  , is_trigger_()
  , is_release_()
{
  for (T_UINT8 i = 0; i < EngineInput::Digital::ID_DIGITAL_MAX; ++i)
  {
    this->input_prepared_[i] = false;
    this->is_trigger_[i] = false;
    this->is_release_[i] = false;
    this->input_hold_[i] = 0;
  }
}

// =================================================================
// Method
// =================================================================
void DigitalInputState::Prepare()
{
  for (T_UINT8 i = 0; i < EngineInput::Digital::ID_DIGITAL_MAX; ++i)
  {
    this->input_prepared_[i] = false;
  }
}

void DigitalInputState::PreInput(EngineInput::Digital::ID id)
{
  if (this->input_prepared_[id])
  {
    return;
  }
  this->input_prepared_[id] = true;
  const T_UINT32 target = (1 << id);
  this->old_state_ = (this->old_state_ & (~target)) | (this->now_state_ & target);
  this->now_state_ = this->now_state_ & (~target);
  this->is_trigger_[id] = false;
  if (this->input_hold_[id] != 0)
  {
    this->is_release_[id] = true;
  }
}

void DigitalInputState::InputValue(EngineInput::Digital::ID id)
{
  NATIVE_ASSERT(this->input_prepared_[id], "DigitalInput:: デバイスの入力処理の前にPrepareInputが呼び出されていません。");
  const T_UINT32 target = (1 << id);
  this->now_state_ |= target;

  this->is_trigger_[id] = target & ~this->old_state_;
  this->is_release_[id] = false;
  if (this->input_hold_[id] < Limit::T_UINT16_MAX)
  {
    ++this->input_hold_[id];
  }
}

void DigitalInputState::PostInput(EngineInput::Digital::ID id)
{
  if (!this->is_release_[id])
  {
    return;
  }
  this->input_hold_[id] = 0;
}
