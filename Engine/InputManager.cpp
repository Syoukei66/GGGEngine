#include "InputManager.h"
#include "EngineInputEvent.h"

InputState::InputState(T_UINT8 player_id, const InputSetting& setting)
  : player_id_(player_id)
  , entities_()
{
  for (const InputEntity& entry : setting.entities_)
  {
    this->entities_[entry.input_id] = entry;
  }
}

void InputState::ClearCache()
{
  //TODO: そもそもキャッシュ作る必要あるかどうか検討
}

bool InputState::AnyButton()
{
  const DigitalInputState* digital = EngineInputState::GetInstance()->GetDigitalInput(this->player_id_);
  for (std::unordered_map<T_UINT8, InputEntity>::iterator itr = this->entities_.begin(), end = this->entities_.end(); itr != end; ++itr)
  {
    const InputEntity& entity = itr->second;
    if (
      digital->IsHold(entity.negative_button) || 
      digital->IsHold(entity.positive_button)
      )
    {
      return true;
    }
  }
  return false;
}

bool InputState::AnyButtonDown()
{
  const DigitalInputState* digital = EngineInputState::GetInstance()->GetDigitalInput(this->player_id_);
  for (std::unordered_map<T_UINT8, InputEntity>::iterator itr = this->entities_.begin(), end = this->entities_.end(); itr != end; ++itr)
  {
    const InputEntity& entity = itr->second;
    if (
      digital->IsTrigger(entity.negative_button) ||
      digital->IsTrigger(entity.positive_button)
      )
    {
      return true;
    }
  }
  return false;
}

bool InputState::AnyButtonUp()
{
  const DigitalInputState* digital = EngineInputState::GetInstance()->GetDigitalInput(this->player_id_);
  for (std::unordered_map<T_UINT8, InputEntity>::iterator itr = this->entities_.begin(), end = this->entities_.end(); itr != end; ++itr)
  {
    const InputEntity& entity = itr->second;
    if (
      digital->IsRelease(entity.negative_button) ||
      digital->IsRelease(entity.positive_button)
      )
    {
      return true;
    }
  }
  return false;
}

bool InputState::AnyAxis()
{
  const AnalogInputState* analog = EngineInputState::GetInstance()->GetAnalogInput(this->player_id_);
  for (std::unordered_map<T_UINT8, InputEntity>::iterator itr = this->entities_.begin(), end = this->entities_.end(); itr != end; ++itr)
  {
    const InputEntity& entity = itr->second;
    if (analog->IsEnabled(entity.axis, entity.dimention))
    {
      return true;
    }
  }
  return false;
}

bool InputState::AnyAxisOrButton()
{
  return this->AnyAxis() || this->AnyButton();
}

T_FLOAT InputState::GetAxis(T_UINT8 id, T_FLOAT dead_range)
{
  const AnalogInputState* analog = EngineInputState::GetInstance()->GetAnalogInput(this->player_id_);
  const DigitalInputState* digital = EngineInputState::GetInstance()->GetDigitalInput(this->player_id_);
  const InputEntity& entity = this->entities_[id];
  if (digital->IsHold(entity.positive_button))
  {
    return 1.0f;
  }
  if (digital->IsHold(entity.negative_button))
  {
    return -1.0f;
  }
  return analog->GetValue(entity.axis, entity.dimention, dead_range);
}

T_FLOAT InputState::GetAxisDown(T_UINT8 id, T_FLOAT dead_range)
{
  const AnalogInputState* analog = EngineInputState::GetInstance()->GetAnalogInput(this->player_id_);
  const DigitalInputState* digital = EngineInputState::GetInstance()->GetDigitalInput(this->player_id_);
  const InputEntity& entity = this->entities_[id];
  if (digital->IsTrigger(entity.positive_button))
  {
    return 1.0f;
  }
  if (digital->IsTrigger(entity.negative_button))
  {
    return -1.0f;
  }
  if (!analog->IsTrigger(entity.axis, entity.dimention, dead_range))
  {
    return 0.0f;
  }
  return analog->GetValue(entity.axis, entity.dimention, dead_range);
}

T_FLOAT InputState::GetAxisUp(T_UINT8 id, T_FLOAT dead_range)
{
  const AnalogInputState* analog = EngineInputState::GetInstance()->GetAnalogInput(this->player_id_);
  const DigitalInputState* digital = EngineInputState::GetInstance()->GetDigitalInput(this->player_id_);
  const InputEntity& entity = this->entities_[id];
  if (digital->IsRelease(entity.positive_button))
  {
    return 1.0f;
  }
  if (digital->IsRelease(entity.negative_button))
  {
    return -1.0f;
  }
  if (!analog->IsRelease(entity.axis, entity.dimention, dead_range))
  {
    return 0.0f;
  }
  return analog->GetOldValue(entity.axis, entity.dimention, dead_range);
}

T_FLOAT InputState::GetAxisDelta(T_UINT8 id)
{
  const AnalogInputState* analog = EngineInputState::GetInstance()->GetAnalogInput(this->player_id_);
  const DigitalInputState* digital = EngineInputState::GetInstance()->GetDigitalInput(this->player_id_);
  const InputEntity& entity = this->entities_[id];
  if (digital->IsTrigger(entity.positive_button))
  {
    return 1.0f;
  }
  if (digital->IsTrigger(entity.negative_button))
  {
    return -1.0f;
  }
  return analog->GetDelta(entity.axis, entity.dimention);
}

bool InputState::GetButton(T_UINT8 id)
{
  const AnalogInputState* analog = EngineInputState::GetInstance()->GetAnalogInput(this->player_id_);
  const DigitalInputState* digital = EngineInputState::GetInstance()->GetDigitalInput(this->player_id_);
  const InputEntity& entity = this->entities_[id];
  if (digital->IsHold(entity.positive_button) || digital->IsHold(entity.negative_button))
  {
    return true;
  }
  return analog->GetValue(entity.axis, entity.dimention) != 0.0f;
}

bool InputState::GetButtonDown(T_UINT8 id)
{
  const AnalogInputState* analog = EngineInputState::GetInstance()->GetAnalogInput(this->player_id_);
  const DigitalInputState* digital = EngineInputState::GetInstance()->GetDigitalInput(this->player_id_);
  const InputEntity& entity = this->entities_[id];
  if (digital->IsTrigger(entity.positive_button) || digital->IsTrigger(entity.negative_button))
  {
    return true;
  }
  return analog->IsTrigger(entity.axis, entity.dimention);
}

bool InputState::GetButtonUp(T_UINT8 id)
{
  const AnalogInputState* analog = EngineInputState::GetInstance()->GetAnalogInput(this->player_id_);
  const DigitalInputState* digital = EngineInputState::GetInstance()->GetDigitalInput(this->player_id_);
  const InputEntity& entity = this->entities_[id];
  if (digital->IsRelease(entity.positive_button) || digital->IsRelease(entity.negative_button))
  {
    return true;
  }
  return analog->IsRelease(entity.axis, entity.dimention);
}

void InputManager::Init(const InputSetting& setting)
{
  this->state_count_ = setting.player_count_;
  this->states_ = new InputState*[this->state_count_];
  for (T_UINT8 i = 0; i < this->state_count_; ++i)
  {
    this->states_[i] = new InputState(i, setting);
  }
}

void InputManager::Uninit()
{
  for (T_UINT8 i = 0; i < this->state_count_; ++i)
  {
    delete this->states_[i];
  }
  delete[] this->states_;
}

void InputManager::ClearCaches()
{
  for (T_UINT8 i = 0; i < this->state_count_; ++i)
  {
    this->states_[i]->ClearCache();
  }
}
