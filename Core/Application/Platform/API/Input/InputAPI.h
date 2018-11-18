#pragma once

#include <Core/Application/Platform/API/APIObject.h>
#include <Core/Application/Input/EngineInputState.h>

class InputManager;
class InputState;
class EngineInputState;
struct ActivityOption;
struct InputSetting;

/*!
 * @brief 入力APIのベースクラス
 */
class InputAPI : public GGAPIObject
{
public:
  enum EnableState
  {
    ONLY_ON_FOCUS,
    ONLY_ON_MOUSE,
    ALWAYS,
  };

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
  bool IsOnCursol();

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
  EnableState enable_state_;
  T_UINT8 cursol_input_id_;
  T_UINT8 state_count_;
  InputState** states_;
  EngineInputState engine_input_state_;

};