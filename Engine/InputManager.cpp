#include "InputManager.h"
#include "EngineInputEvent.h"

InputState::InputState(T_UINT8 player_id, const InputSetting& setting)
  : player_id_(player_id)
  , entities_()
{
  for (std::deque<InputEntity>::const_iterator itr = setting.entities_.begin(); itr != setting.entities_.end(); ++itr)
  {
    this->entities_[(*itr).input_id] = (*itr);
  }
}

void InputState::ClearCache()
{
  //TODO: そもそもキャッシュ作る必要あるかどうか検討
}

bool InputState::AnyButton()
{
  const DigitalInputState* digital = EngineInputState::GetInstance()->GetDigitalInput(this->player_id_);
  for (std::map<T_UINT8, InputEntity>::iterator itr = this->entities_.begin(); itr != this->entities_.end(); ++itr)
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

bool InputState::AnyAxis()
{
  const AnalogInputState* analog = EngineInputState::GetInstance()->GetAnalogInput(this->player_id_);
  for (std::map<T_UINT8, InputEntity>::iterator itr = this->entities_.begin(); itr != this->entities_.end(); ++itr)
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
  const T_FLOAT value = analog->GetValue(entity.axis, entity.dimention, -1.0f, 1.0f);
  if (fabs(value) < dead_range)
  {
    return 0.0f;
  }
  return value;
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
  return analog->GetValue(entity.axis, entity.dimention, -1.0f, 1.0f) != 0.0f;
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
}

void InputManager::ClearCaches()
{
  for (T_UINT8 i = 0; i < this->state_count_; ++i)
  {
    this->states_[i]->ClearCache();
  }
}
