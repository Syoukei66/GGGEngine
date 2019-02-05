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
  bool AnyButton() const;
  bool AnyButtonDown() const;
  bool AnyButtonUp() const;
  bool AnyAxis() const;
  bool AnyAxisOrButton() const;
  T_FLOAT GetAxis(T_UINT8 id, T_FLOAT dead_range = 0.1f) const;
  T_FLOAT GetAxisDown(T_UINT8 id, T_FLOAT dead_range = 0.1f) const;
  T_FLOAT GetAxisUp(T_UINT8 id, T_FLOAT dead_range = 0.1f) const;
  T_FLOAT GetAxisDelta(T_UINT8 id) const;
  bool GetButton(T_UINT8 id) const;
  bool GetButtonDown(T_UINT8 id) const;
  bool GetButtonUp(T_UINT8 id) const;

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT8 player_id_;
  std::unordered_map<T_UINT8, InputEntity> entities_;
  DigitalInputState digital_input_;
  AnalogInputState analog_input_;

};