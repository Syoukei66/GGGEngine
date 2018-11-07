#pragma once

#include <Core/Application/Platform//API/APIObject.h>
#include <Core/Application/Input/InputSetting.h>
#include <Core/Application/Input/InputState.h>

class InputManager;
class EngineInputState;
struct ActivityOption;

/*!
 * @brief 入力APIのベースクラス
 */
class InputAPI : public GGAPIObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
public:
  GG_INIT_FUNC_1(InputAPI, const InputSetting& setting);
  GG_DESTRUCT_FUNC(InputAPI);

  // =================================================================
  // Methods
  // =================================================================
public:
  void Update();

protected:
  virtual void InputProcess(EngineInputState* state) = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE T_UINT8 GetStateCount()
  {
    return this->state_count_;
  }
  GG_INLINE InputState* GetState(T_UINT8 player_id)
  {
    return this->states_[player_id];
  }
  GG_INLINE EngineInputState* GetEngineInputState()
  {
    return &this->engine_input_state_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT8 state_count_;
  InputState** states_;
  EngineInputState engine_input_state_;

};