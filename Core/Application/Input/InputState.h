#pragma once

#include "InputSetting.h"
#include "DigitalInput.h"
#include "AnalogInput.h"
#include "EngineInputState.h"

/*!
 * @brief プレイヤー１人あたりの入力状態を表すクラス
 */
class InputState
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  InputState(T_UINT8 player_id, const InputSetting& setting);

  // =================================================================
  // Methods
  // =================================================================
public:
  void Update(const EngineInputState& state);

public:
  bool AnyButton();
  bool AnyButtonDown();
  bool AnyButtonUp();
  bool AnyAxis();
  bool AnyAxisOrButton();
  T_FLOAT GetAxis(T_UINT8 id, T_FLOAT dead_range = 0.1f);
  T_FLOAT GetAxisDown(T_UINT8 id, T_FLOAT dead_range = 0.1f);
  T_FLOAT GetAxisUp(T_UINT8 id, T_FLOAT dead_range = 0.1f);
  T_FLOAT GetAxisDelta(T_UINT8 id);
  bool GetButton(T_UINT8 id);
  bool GetButtonDown(T_UINT8 id);
  bool GetButtonUp(T_UINT8 id);

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT8 player_id_;
  std::unordered_map<T_UINT8, InputEntity> entities_;
  const DigitalInputState* digital_input_;
  const AnalogInputState* analog_input_;
};