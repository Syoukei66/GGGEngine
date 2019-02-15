#include "InputState.h"

InputState::InputState(T_UINT8 player_id, const InputSetting& setting)
  : player_id_(player_id)
  , entities_()
  , digital_input_(DigitalInputState::NULL_INPUT)
  , analog_input_(AnalogInputState::NULL_INPUT)
{
  for (const InputEntity& entry : setting.entities_)
  {
    this->entities_[entry.input_id] = entry;
  }
}

void InputState::Update(const EngineInputState& state)
{
  this->analog_input_ = state.GetAnalogInput(this->player_id_);
  this->digital_input_ = state.GetDigitalInput(this->player_id_);
}

bool InputState::AnyButton() const
{
  for (const auto& itr : this->entities_)
  {
    const InputEntity& entity = itr.second;
    if (
      this->digital_input_.IsHold(entity.negative_button) ||
      this->digital_input_.IsHold(entity.positive_button)
      )
    {
      return true;
    }
  }
  return false;
}

bool InputState::AnyButtonDown() const
{
  for (const auto& itr : this->entities_)
  {
    const InputEntity& entity = itr.second;
    if (
      this->digital_input_.IsTrigger(entity.negative_button) ||
      this->digital_input_.IsTrigger(entity.positive_button)
      )
    {
      return true;
    }
  }
  return false;
}

bool InputState::AnyButtonUp() const
{
  for (const auto& itr : this->entities_)
  {
    const InputEntity& entity = itr.second;
    if (
      this->digital_input_.IsRelease(entity.negative_button) ||
      this->digital_input_.IsRelease(entity.positive_button)
      )
    {
      return true;
    }
  }
  return false;
}

bool InputState::AnyAxis() const
{
  for (const auto& itr : this->entities_)
  {
    const InputEntity& entity = itr.second;
    if (this->analog_input_.IsEnabled(entity.axis, entity.dimention))
    {
      return true;
    }
  }
  return false;
}

bool InputState::AnyAxisOrButton() const
{
  return this->AnyAxis() || this->AnyButton();
}

T_FLOAT InputState::GetAxis(T_UINT8 id, T_FLOAT dead_range) const
{
  const InputEntity& entity = this->entities_.at(id);
  if (this->digital_input_.IsHold(entity.positive_button))
  {
    return 1.0f;
  }
  if (this->digital_input_.IsHold(entity.negative_button))
  {
    return -1.0f;
  }
  return this->analog_input_.GetValue(entity.axis, entity.dimention, dead_range);
}

T_FLOAT InputState::GetAxisDown(T_UINT8 id, T_FLOAT dead_range) const
{
  const InputEntity& entity = this->entities_.at(id);
  if (this->digital_input_.IsTrigger(entity.positive_button))
  {
    return 1.0f;
  }
  if (this->digital_input_.IsTrigger(entity.negative_button))
  {
    return -1.0f;
  }
  if (!this->analog_input_.IsTrigger(entity.axis, entity.dimention, dead_range))
  {
    return 0.0f;
  }
  return this->analog_input_.GetValue(entity.axis, entity.dimention, dead_range);
}

T_FLOAT InputState::GetAxisUp(T_UINT8 id, T_FLOAT dead_range) const
{
  const InputEntity& entity = this->entities_.at(id);
  if (this->digital_input_.IsRelease(entity.positive_button))
  {
    return 1.0f;
  }
  if (this->digital_input_.IsRelease(entity.negative_button))
  {
    return -1.0f;
  }
  if (!this->analog_input_.IsRelease(entity.axis, entity.dimention, dead_range))
  {
    return 0.0f;
  }
  return this->analog_input_.GetOldValue(entity.axis, entity.dimention, dead_range);
}

T_FLOAT InputState::GetAxisDelta(T_UINT8 id) const
{
  const InputEntity& entity = this->entities_.at(id);
  if (this->digital_input_.IsTrigger(entity.positive_button))
  {
    return 1.0f;
  }
  if (this->digital_input_.IsTrigger(entity.negative_button))
  {
    return -1.0f;
  }
  return this->analog_input_.GetDelta(entity.axis, entity.dimention);
}

bool InputState::GetButton(T_UINT8 id) const
{
  const InputEntity& entity = this->entities_.at(id);
  if (this->digital_input_.IsHold(entity.positive_button) || this->digital_input_.IsHold(entity.negative_button))
  {
    return true;
  }
  return this->analog_input_.GetValue(entity.axis, entity.dimention) != 0.0f;
}

bool InputState::GetButtonDown(T_UINT8 id) const
{
  const InputEntity& entity = this->entities_.at(id);
  if (this->digital_input_.IsTrigger(entity.positive_button) || this->digital_input_.IsTrigger(entity.negative_button))
  {
    return true;
  }
  return this->analog_input_.IsTrigger(entity.axis, entity.dimention);
}

bool InputState::GetButtonUp(T_UINT8 id) const
{
  const InputEntity& entity = this->entities_.at(id);
  if (this->digital_input_.IsRelease(entity.positive_button) || this->digital_input_.IsRelease(entity.negative_button))
  {
    return true;
  }
  return this->analog_input_.IsRelease(entity.axis, entity.dimention);
}
